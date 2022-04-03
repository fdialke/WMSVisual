#include "stdafx.h"
#include "WMSLocation.h"

#define WMS_MAXLOCATIONNAMELENGTH	10		// макс длина имени ячейке для вывдоа

WMSLocation::WMSLocation(	std::string&		_inventLocation, 
							std::string&		_location, 
							DWORD				_xPosition,
							DWORD				_yPosition,
							DWORD				_zPosition,
							LocationRotation	_rotation,
							float				_fillingPercentage):
m_FillingPercentage(_fillingPercentage),
m_InventLocation(_inventLocation),
m_Location(_location),
m_Rotation(_rotation),
m_xPosition(_xPosition),
m_yPosition(_yPosition),
m_zPosition(_zPosition),
m_bShow(true)
{
	XMMATRIX	locationMatrix = WMSLocation::GetRotationMatrix(_rotation);
	XMMATRIX	itemMatrix;

	/*
	switch(_rotation)
	{
		case FACE:
			break;
		case RIGHT:
			locationMatrix = locationMatrix * XMMatrixRotationY(MathHelper::Pi/2);
			break;
		case BACK:
			locationMatrix = locationMatrix * XMMatrixRotationY(MathHelper::Pi);
			break;
		case LEFT:
			locationMatrix = locationMatrix * XMMatrixRotationY(-MathHelper::Pi/2);
			break;
		// ячейка может быть повернута в разные стороны 
	}
	*/

	itemMatrix		= locationMatrix * 
						XMMatrixScaling(m_FillingPercentage, m_FillingPercentage,m_FillingPercentage) * 
						XMMatrixTranslation(xSize +_xPosition*dx, 
											ySize +_yPosition*dy - GeometryGenerator::getPalletHeight() * (1.0f - m_FillingPercentage), 
											zSize +_zPosition*dz);
	// мировая матрица = кубик уменьшается до соответствующего процента, потом переносится в точку самой ячейки и сдвигается вниз до уровня паллеты

	locationMatrix = locationMatrix * XMMatrixTranslation(xSize+_xPosition*dx, ySize+_yPosition*dy, zSize+_zPosition*dz);
	// мипровая матрица = ячейка переносится по своим относительным координатам

	XMStoreFloat4x4(&m_WorldMatrixLocation, locationMatrix);
	XMStoreFloat4x4(&m_ItemWorldMatrixLocation, itemMatrix);

	XMFLOAT3 vMinf3(1.0f, 1.0f, 1.0f);
	XMFLOAT3 vMaxf3(-1.0f, -1.0f, -1.0f);
	
	XMVECTOR vMin = XMLoadFloat3(&vMinf3);
	XMVECTOR vMax = XMLoadFloat3(&vMaxf3);

	XMStoreFloat3(&m_BoundBox.Center, 0.5f * (vMin + vMax));
	XMStoreFloat3(&m_BoundBox.Extents, 0.5f * (vMax - vMin));
	// сохраняем окружающий куб - по сути это куб ячейки
}
WMSLocation::~WMSLocation()
{

}
XMMATRIX	WMSLocation::GetRotationMatrix(LocationRotation	_rotation)
{
	XMMATRIX	I = XMMatrixIdentity();

	switch(_rotation)
	{
		case FACE:
			break;
		case RIGHT:
			return I * XMMatrixRotationY(MathHelper::Pi/2);
			break;
		case BACK:
			return I * XMMatrixRotationY(MathHelper::Pi);
			break;
		case LEFT:
			return I * XMMatrixRotationY(-MathHelper::Pi/2);
			break;
	}

	return I;
}
void WMSLocationWrapper::AddLocation(	std::string&		_inventLocation, 
										std::string&		_location, 
										DWORD				_xPosition,
										DWORD				_yPosition,
										DWORD				_zPosition,
										LocationRotation	_rotation,
										float				_fillingPercentage)
{
	WMSLocation		locationLocal(_inventLocation, _location, _xPosition, _yPosition, _zPosition, _rotation, adjustPercent(_fillingPercentage));

	m_mapLocation.insert(std::pair<std::string, WMSLocation>(locationLocal.getMixName(), locationLocal));

	if (_xPosition < xMin)	xMin = _xPosition;
	if (_xPosition > xMax)	xMax = _xPosition;
	if (_yPosition < yMin)	yMin = _yPosition;
	if (_yPosition > yMax)	yMax = _yPosition;
	if (_zPosition < zMin)	zMin = _zPosition;
	if (_zPosition > zMax)	zMax = _zPosition;

	if (_yPosition == 0)
	{
		m_mapGrid.insert(std::pair<GridPos, Node>(GridPos(_xPosition, _zPosition), Node(_xPosition, _zPosition)));
	}
}
std::string	WMSLocation::getMixName(std::string & _inventLocation, std::string & _location)
{
	return _inventLocation + "_" + _location;
}
std::string			WMSLocation::getMixName()
{
	return WMSLocation::getMixName(m_InventLocation, m_Location);
}
void WMSLocationWrapper::BuildGrid()
{
	for (DWORD	x = xMin; x <= xMax; x++)
	{
		for (DWORD	y = yMin; y <= yMax; y++)
		{
			for (DWORD	z = zMin; z <= zMax; z++)
			{
				auto localNode = m_mapGrid.find(GridPos(x, z));
				if (localNode == m_mapGrid.end())
				{
					m_mapGrid.insert(std::pair<GridPos, Node>(GridPos(x, z), Node(x, z, true)));
				}
			}
		}
	}
	// заполнили оставшиеся клетки грида значениями, считаем что все они проходные, т.к. "стены" были заполнены при добавлении ячеек нулевой высоты
}
void WMSLocationWrapper::BuildInstanceData(	std::vector<InstancedData>&		pInstanceData,
											std::vector<ArrayTextPosition>&	pArrayTextPosition,
											TextWrapper&					pTextWrapper)
{
	BuildGrid();

	pInstanceData.resize(m_mapLocation.size());
	pArrayTextPosition.resize(WMS_MAXLOCATIONNAMELENGTH * m_mapLocation.size());

	DWORD	i = 0, j =0, k = 0, locationNameLength = 0, shift = 0;
	
	for (auto it = m_mapLocation.begin(); it != m_mapLocation.end(); ++it)	
	{
		locationNameLength			= min(WMS_MAXLOCATIONNAMELENGTH, it->second.m_Location.size());
		shift						= (WMS_MAXLOCATIONNAMELENGTH - locationNameLength) / 2;
		pInstanceData[i].faceTexNum	= i;
		pInstanceData[i].World		= it->second.m_WorldMatrixLocation;
		pInstanceData[i].WorldItem	= it->second.m_ItemWorldMatrixLocation;

		for (j = 0; j < WMS_MAXLOCATIONNAMELENGTH; j++)
		{
			if (j >= shift && j < (shift + locationNameLength)) // размещаю текст посередине строки из 10 символов -> "_A2-38-17_"
			{
				pArrayTextPosition[WMS_MAXLOCATIONNAMELENGTH * i + j].iPosition	= pTextWrapper.getCharPosition(it->second.m_Location[j - shift]);
			} else
			{
				pArrayTextPosition[WMS_MAXLOCATIONNAMELENGTH * i + j].iPosition	= pTextWrapper.getCharPosition(" ");
			
			}
		}

		it->second.m_InstanceNum = i;

		i++;
	}
}
WMSLocation* WMSLocationWrapper::GetClosestLocation(XMVECTOR& rayOrigin, XMVECTOR& rayDir, XMMATRIX& invView)
{
	WMSLocation*	pRetClosest = nullptr;
	float			tClosest = MathHelper::Infinity, tMinBox;

	float tmin = MathHelper::Infinity;
	for (auto it = m_mapLocation.begin(); it != m_mapLocation.end(); ++it)
	{
		if (it->second.m_bShow == false) continue;

		XMMATRIX W = XMLoadFloat4x4(&it->second.m_WorldMatrixLocation);
		XMMATRIX invWorld = XMMatrixInverse(&XMMatrixDeterminant(W), W);

		XMMATRIX toLocal = XMMatrixMultiply(invView, invWorld);

		XMVECTOR	rayOriginLocal = XMVector3TransformCoord(rayOrigin, toLocal);
		XMVECTOR	rayDirLocal = XMVector3TransformNormal(rayDir, toLocal);

		// Make the ray direction unit length for the intersection tests.
		rayDirLocal = XMVector3Normalize(rayDirLocal);

		if(XNA::IntersectRayAxisAlignedBox(rayOriginLocal, rayDirLocal, &it->second.m_BoundBox, &tMinBox) && tMinBox <= tmin)
		{
			for (size_t i = 0; i < box.Indices.size() / 3; i++)
			{
				/*
				UINT i0 = box.Indices[i*3+0];
				UINT i1 = box.Indices[i*3+1];
				UINT i2 = box.Indices[i*3+2];

				XMVECTOR v0 = XMLoadFloat3(&box.Vertices[i0].Position);
				XMVECTOR v1 = XMLoadFloat3(&box.Vertices[i1].Position);
				XMVECTOR v2 = XMLoadFloat3(&box.Vertices[i2].Position);
				*/

				float t = 0.0f;
				if(XNA::IntersectRayTriangle(	rayOriginLocal, 
												rayDirLocal, 
												XMLoadFloat3(&box.Vertices[box.Indices[i*3+0]].Position), // v0
												XMLoadFloat3(&box.Vertices[box.Indices[i*3+1]].Position), //v1
												XMLoadFloat3(&box.Vertices[box.Indices[i*3+2]].Position), //v2
												&t))
				{
					if( t < tmin )
					{
						// This is the new nearest picked triangle.
						tmin = t;
						pRetClosest = &it->second;
					}
				}
				
			}
		}
	}

	return pRetClosest;
}
ULONG WMSLocationWrapper::MapSize()
{
	return m_mapLocation.size();
}
void WMSLocationWrapper::UpdateFillLocation(std::string& il, std::string& wl, float percent)
{
	auto it = m_mapLocation.find(WMSLocation::getMixName(il, wl));

	if (it != m_mapLocation.end())
	{
		it->second.m_FillingPercentage = adjustPercent(percent);
	}
}
void WMSLocationWrapper::UpdateSceneFill(std::vector<InstancedData>& pData, DWORD* pdwInstanceSize)
{
	*pdwInstanceSize = 0;

	/*
	XMMATRIX	faceMatrix	= XMMatrixIdentity(),
				rightMatrix	= XMMatrixIdentity() * XMMatrixRotationY(MathHelper::Pi/2),
				backMatrix	= XMMatrixIdentity() * XMMatrixRotationY(MathHelper::Pi),
				leftMatrix	= XMMatrixIdentity() * XMMatrixRotationY(-MathHelper::Pi/2);
	*/

	for (auto it = m_mapLocation.begin(); it != m_mapLocation.end(); ++it)	
	{
		XMMATRIX	rotateMatrix = WMSLocation::GetRotationMatrix(it->second.m_Rotation);
		
		XMStoreFloat4x4(&pData[it->second.m_InstanceNum].WorldItem ,
						rotateMatrix *
						XMMatrixScaling(it->second.m_FillingPercentage, 
										it->second.m_FillingPercentage,
										it->second.m_FillingPercentage) * 
						XMMatrixTranslation(xSize + it->second.m_xPosition * dx, 
											ySize + it->second.m_yPosition * dy - GeometryGenerator::getPalletHeight() * (1.0f - it->second.m_FillingPercentage), 
											zSize + it->second.m_zPosition * dz));

		(*pdwInstanceSize)++;
	}
}
void WMSLocationWrapper::DeleteAllLocations()
{
	m_mapLocation.clear();

	xMin = yMin = zMin = -1;
	xMax = yMax = zMax = 0;

	m_mapGrid.clear();

	m_listOpenNode.clear();

}
WMSLocationWrapper::WMSLocationWrapper():
m_minFillPercent(0.0f),
m_maxFillPercent(1.0f),
xMin(-1),
yMin(-1),
zMin(-1),
xMax(0),
yMax(0),
zMax(0)
{
	GeometryGenerator	geoGen;

	geoGen.CreateBox(1.0f, 1.0f, 1.0f, box);
}
WMSLocationWrapper::~WMSLocationWrapper()
{

}
HRESULT			WMSLocationWrapper::get_minFillPercent(FLOAT* pVal)
{
	*pVal = m_minFillPercent;
	return S_OK;
}
HRESULT			WMSLocationWrapper::put_minFillPercent(FLOAT newVal)
{
	if (m_mapLocation.size()) return E_FAIL;

	m_minFillPercent = newVal;
	return S_OK;
}
HRESULT			WMSLocationWrapper::get_maxFillPercent(FLOAT* pVal)
{
	*pVal = m_maxFillPercent;
	return S_OK;
}
HRESULT			WMSLocationWrapper::put_maxFillPercent(FLOAT newVal)
{
	if (m_mapLocation.size()) return E_FAIL;

	m_maxFillPercent = newVal;
	return S_OK;
}
float WMSLocationWrapper::adjustPercent(float fillPercent)
{
	if (fillPercent < m_minFillPercent)
		return m_minFillPercent;

	if (fillPercent > m_maxFillPercent)
		return m_maxFillPercent;

	return fillPercent;
}
HRESULT	WMSLocationWrapper::SetLocationStatus(std::string& il, std::string& wl, SHORT bShow, DWORD dwStatus, WMSLocation** pPickedLocation)
{
	auto it = m_mapLocation.find(WMSLocation::getMixName(il, wl));

	if (it == m_mapLocation.end()) return E_FAIL;

	it->second.m_bShow = bShow ? true : false;

	if (pPickedLocation[0]  && pPickedLocation[0]->getMixName() == it->second.getMixName())
		pPickedLocation[0] = nullptr;

	return S_OK;
}
void WMSLocationWrapper::UpdateSceneHelper(std::vector<InstancedData>& globalInstanceDataArray, InstancedData* pData, DWORD* pdwVisibleObject)
{
	*pdwVisibleObject = 0;

	for (auto it = m_mapLocation.begin(); it != m_mapLocation.end(); ++it)	
	{
		if (it->second.m_bShow)
		{
			pData[*pdwVisibleObject] = globalInstanceDataArray[it->second.m_InstanceNum];
			(*pdwVisibleObject)++;
		}
	}
}
void WMSLocationWrapper::GetMinMax(MinMax* xMinMax, MinMax* yMinMax, MinMax* zMinMax)
{
	xMinMax->min	= (float)xMin;
	xMinMax->max	= (float)xMax;

	yMinMax->min	= (float)yMin;
	yMinMax->max	= (float)yMax;

	zMinMax->min	= (float)zMin;
	zMinMax->max	= (float)zMax;
}
WMSLocation*	WMSLocationWrapper::GetLocation(std::string& _inventLocation, std::string& _wmsLocation)
{
	auto it = m_mapLocation.find(WMSLocation::getMixName(_inventLocation, _wmsLocation));

	return (it == m_mapLocation.end()) ? nullptr : &it->second;
}
