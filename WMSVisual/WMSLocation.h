#pragma once
#ifndef WMSLOCATION_H
#define WMSLOCATION_H

#include "stdafx.h"
#include <string>
#include <map>
#include <vector>
#include "MathHelper.h"
#include "Vertex.h"
#include "GeometryGenerator.h"
#include "TextWrapper.h"
#include "xnacollision.h"
#include <list>

const	float width = 1.0f;
const	float height = 1.0f;
const	float depth = 1.0f;
	
const	float xSize = -0.5f*width;
const	float ySize = -0.5f*height;
const	float zSize = -0.5f*depth;
/*
const	float dx = 1.0f;//width / (n-1);
const	float dy = 1.0f;//height / (n-1);
const 	float dz = 1.0f;//depth / (n-1);
*/

#define WMS_SHIFTCUBE				0.005f	// сдвиг каждого из объектов дл€ борьбы с z-fighting

const	float dx = 1.0f + WMS_SHIFTCUBE;//width / (n-1); // чтобы не было Z-Fighting делаем сдвиг 
const	float dy = 1.0f + WMS_SHIFTCUBE;//height / (n-1);
const 	float dz = 1.0f + WMS_SHIFTCUBE;//depth / (n-1);


typedef 
enum LocationRotation
    {	
		FACE			= 0,	//				\/
		RIGHT			= 1,	//				<-
		BACK			= 2,	//				^
		LEFT			= 3		//				->
    } 	LocationRotation;

struct MinMax
{
	float	min;
	float	max;
};

struct GridPos
{
public:
	int	x;
	int	y;

	GridPos(int	iX, int	iY)
	{
		x	= iX;
		y	= iY;
	}
	GridPos(GridPos& b)
	{
		x	= b.x;
		y	= b.y;
	}
	long		getHash() const
	{
		return (long)x * 10000 + (long)y;
	}
	bool operator ==(GridPos& b)
	{
		return x == b.x && y == b.y;
	}
	bool operator !=(GridPos& b)
	{
		return !(*this == b);
	}
	friend bool operator < (const GridPos& a, const GridPos& b)
	{
		return a.getHash() < b.getHash();
	}
};


class Node // класс дл€ хранени€ данных по поиску пути - используетс€ алгоритм "ќртогональный JPS", 
			// дл€ расчета эвристики - Manhattan
{
public:
	int	x;
	int	y;
	bool	walkable;
	float	heuristicStartToEndLen;
	float	startToCurNodeLen;
	float	heuristicCurNodeToEndLen;
	bool	isOpened;
	bool	isClosed;
	Node*	parent;

	Node(int iX, int iY, bool iWalkable = false)
	{
		x = iX;
		y = iY;
		walkable					= iWalkable;
		heuristicStartToEndLen		= 0;
		startToCurNodeLen			= 0;
		heuristicCurNodeToEndLen	= 0;
		isOpened	= false;
		isClosed	= false;
		parent		= nullptr;
	}
	Node(Node & b)
	{
		x = b.x;
		y = b.y;
		walkable	= b.walkable;
		heuristicStartToEndLen	= b.heuristicStartToEndLen;
		startToCurNodeLen		= b.startToCurNodeLen;
		heuristicCurNodeToEndLen	= b.heuristicCurNodeToEndLen;
		isOpened	= b.isOpened;
		isClosed	= b.isClosed;
		parent		= b.parent;
	}
	
	std::list<GridPos> Backtrace(Node&	iNode)
	{
		std::list<GridPos> path;

		path.push_back(GridPos(iNode.x, iNode.y));
		while (iNode.parent != nullptr)
		{
			iNode = *iNode.parent;
			path.push_back(GridPos(iNode.x, iNode.y));
		}

		path.reverse();
		return path;
	}

	bool operator ==(Node& b)
	{
		return x == b.x && y == b.y;
	}
	bool operator !=(Node& b)
	{
		return !(*this == b);
	}
	friend bool operator < (const Node& a, const Node& b)
	{
		float	result = a.heuristicStartToEndLen - b.heuristicStartToEndLen;

		return (result < 0.0f) ? false : true;
	}
};

class WMSLocation
{
public:
	WMSLocation(	std::string&		_inventLocation, 
					 std::string&		_location, 
					 DWORD				_xPosition,
					 DWORD				_yPosition,
					 DWORD				_zPosition,
					 LocationRotation	_rotation,
					 float				_fillingPercentage);
	~WMSLocation();

	static std::string	getMixName(std::string & _inventLocation, std::string & _location);
	std::string			getMixName();

	static XMMATRIX		GetRotationMatrix(LocationRotation	_rotation);


	XMFLOAT4X4		m_WorldMatrixLocation;
	XMFLOAT4X4		m_ItemWorldMatrixLocation;

	float			m_FillingPercentage;	
	std::string		m_InventLocation;
	std::string		m_Location;

	XNA::AxisAlignedBox m_BoundBox;

	DWORD			m_InstanceNum;
	LocationRotation	m_Rotation;

	DWORD				m_xPosition, m_yPosition, m_zPosition;
	bool				m_bShow;
};
class WMSLocationWrapper
{
public:
	WMSLocationWrapper();
	~WMSLocationWrapper();

	void AddLocation(std::string&		_inventLocation, 
					 std::string&		_location, 
					 DWORD				_xPosition,
					 DWORD				_yPosition,
					 DWORD				_zPosition,
					 LocationRotation	_rotation,
					 float				_fillingPercentage);
	void AddLocation(const char *		_inventLocation, 
					 const char *		_location, 
					 DWORD				_xPosition,
					 DWORD				_yPosition,
					 DWORD				_zPosition,
					 LocationRotation	_rotation,
					 float				_fillingPercentage)
	{
		std::string	lInventLocation = _inventLocation;
		std::string lLocation		= _location;

		AddLocation(lInventLocation, lLocation, _xPosition, _yPosition, _zPosition, _rotation, _fillingPercentage);
	}


	void			BuildInstanceData(	std::vector<InstancedData>&		pInstanceData,
										std::vector<ArrayTextPosition>&	pArrayTextPosition,
										TextWrapper&					pTextWrapper);

	WMSLocation*	GetClosestLocation(XMVECTOR& rayOrigin, XMVECTOR& rayDir,XMMATRIX& invView );
	void			DeleteAllLocations();
	ULONG			MapSize();
	void			UpdateFillLocation(std::string& il, std::string& wl, float percent);
	void			UpdateSceneFill(std::vector<InstancedData>& pData, DWORD* pdwInstanceSize);
	HRESULT			get_minFillPercent(FLOAT* pVal);
	HRESULT			put_minFillPercent(FLOAT newVal);
	HRESULT			get_maxFillPercent(FLOAT* pVal);
	HRESULT			put_maxFillPercent(FLOAT newVal);
	HRESULT			SetLocationStatus(std::string& il, std::string& wl, SHORT bShow, DWORD dwStatus, WMSLocation** pPickedLocation);
	void			UpdateSceneHelper(std::vector<InstancedData>& globalInstanceDataArray, InstancedData* pData, DWORD* pdwVisibleObject);

	void			GetMinMax(MinMax* xMinMax, MinMax* yMinMax, MinMax* zMinMax);

	WMSLocation*	GetLocation(std::string& _inventLocation, std::string& _wmsLocation);

	void			BuildGrid();

private:
	float			adjustPercent(float fillPercent);


private:
	std::map<std::string, WMSLocation>	m_mapLocation;	// Map всех €чеек

	std::map<GridPos, Node>					m_mapGrid;		// грид всех точек на полу склада, учитываютс€ только €чейки с высотой = 0
	std::list<Node>							m_listOpenNode;	// набор открытых нод
	

	GeometryGenerator::MeshData		box;

	float							m_minFillPercent, m_maxFillPercent;

	DWORD	xMin, xMax;
	DWORD	yMin, yMax;
	DWORD	zMin, zMax;
};

#endif