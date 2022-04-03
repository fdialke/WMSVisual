#include "stdafx.h"
#include "WMSVisualControl.h"
#include "WMSCamera.h"
#include "WMSTimer.h"
#include "Vertex.h"
#include "xnacollision.h"
#include "Effects.h"
#include "RenderStates.h"
#include "TextWrapper.h"
#include "GeometryGenerator.h"
#include "WMSLocation.h"
#include "WMSSky.h"
#include "WarehouseRoom.h"

//LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam);
//static HHOOK hhk;
//static CWMSVisualControl::CWMSVisualControlImpl * globalImpl;

class CWMSVisualControl::CWMSVisualControlImpl
{
public:
	CWMSVisualControl	* _this;

	POINT mLastMousePos;

	bool	mAppPaused;
	bool    mMinimized;
	bool    mMaximized;
	bool    mResizing;

	WMSCamera		mCam;

	void* operator new(size_t i)
	{
		return _aligned_malloc(i, 16);
	}

	void operator delete(void* p)
	{
		_aligned_free(p);
	}
	float AspectRatio()const
	{
		return static_cast<float>(mClientWidth) / mClientHeight;
	}


	CWMSVisualControlImpl(CWMSVisualControl * wrapper);
	~CWMSVisualControlImpl();
	LRESULT OnCreate(UINT, WPARAM, LPARAM, BOOL&);
	LRESULT OnDestroy(UINT, WPARAM, LPARAM, BOOL&);
	LRESULT OnSize(UINT, WPARAM, LPARAM, BOOL&);
	LRESULT OnTimer(UINT, WPARAM, LPARAM, BOOL&);
	HRESULT OnDraw(ATL_DRAWINFO& di);
	
	bool Init();
	void OnResize();
	void UpdateScene(float dt);
	void DrawScene(); 

	bool InitDirect3D();

	HRESULT InitD3D();
	HRESULT InitShaders();
	HRESULT InitGeometry();

	LRESULT OnMouseUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnKeyUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnEnterSizeMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnExitSizeMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	void	GetPickedLocation(std::string&	inventLocation, std::string& wmsLocation);

	HRESULT DeleteAllLocations();
	HRESULT AddLocation(std::string& InventLocationName, std::string& WMSLocationName, ULONG ShiftX, ULONG ShiftY, ULONG ShiftZ, BYTE Rotation, FLOAT FillingPercent);
	HRESULT BuildScene();
	HRESULT UpdateLocationFill(std::string& InventLocationName, std::string& wmsLocationName, float fNewPercent);
	HRESULT UpdateSceneFill();
	HRESULT	SetLocationStatus(std::string& il, std::string& wl, SHORT bShow, DWORD dwStatus);

	HRESULT SetSourceLocation(std::string& inventLocationName, std::string& wmsLocationName);
	HRESULT SetDestinationLocation(std::string& inventLocationName, std::string& wmsLocationName);
	HRESULT ClearSourceDestLocation();

public:
	WMSTimer			mTimer;
	bool				mThreadRun;
	WMSLocationWrapper	locationWrapper;


protected:
	UINT      m4xMsaaQuality;

	CComPtr<ID3D11Device>			md3dDevice;
	CComPtr<ID3D11DeviceContext>	md3dImmediateContext;
	CComPtr<IDXGISwapChain>			mSwapChain;
	CComPtr<ID3D11Texture2D>		mDepthStencilBuffer;
	CComPtr<ID3D11RenderTargetView> mRenderTargetView;
	CComPtr<ID3D11DepthStencilView> mDepthStencilView;
	D3D11_VIEWPORT					mScreenViewport;
	D3D_DRIVER_TYPE					md3dDriverType;

	int								mClientWidth;
	int								mClientHeight;
	bool							mEnable4xMsaa;

private:
	void BuildMeshGeometryBuffers();
	void Pick(int sx, int sy);

private:

	int mBoxVertexOffset;
	UINT mBoxIndexOffset;
	UINT mBoxIndexCount;

//	CComPtr<ID3D11Buffer> mMeshVB;
//	CComPtr<ID3D11Buffer> mMeshIB;

	// Keep system memory copies of the Mesh geometry for picking.
//	std::vector<Vertex::Basic32> mMeshVertices;
//	std::vector<UINT> mMeshIndices;

	XNA::AxisAlignedBox mMeshBox;

	DirectionalLight mDirLights[3];
	Material mMeshMat;

	// Define transformations from local spaces to world space.
//	XMFLOAT4X4 mMeshWorld;


	bool	wasInit;

	TextWrapper		textWrapper;

	std::vector<InstancedData>		mInstancedData;
	std::vector<ArrayTextPosition>	mArrayTextPosition;

	DWORD						mVisibleObjectCount;


	UINT	mTransparentVBCount;
	UINT	mTransparentVICount;

	ID3D11BlendState*			TransparentBS;
	ID3D11Buffer*				mTransparentVB;
	ID3D11Buffer*				mTransparentIB;
	ID3D11Buffer*				mBoxVB;
	ID3D11Buffer*				mBoxIB;
	ID3D11Buffer*				mInstancedBuffer;
	ID3D11Buffer*				mArrayPositionBuffer;
	ID3D11ShaderResourceView*	mDiffuseMapSRV;
	ID3D11ShaderResourceView*	mLocationMap;
	ID3D11ShaderResourceView*	mItemFaceMap;
	ID3D11ShaderResourceView*	mItemSideMap;
	ID3D11ShaderResourceView*	mItemTopMap;
	ID3D11ShaderResourceView*	mTransparentMap;
	ID3D11ShaderResourceView*	mArrayPositionMap;

	Material mBoxMat;
	Material mWavesMat;

	XMFLOAT4X4 mTexTransform;
	XMFLOAT4X4 mBoxWorld;

	XMFLOAT2 mWaterTexOffset;
	XMFLOAT4X4 mWaterTexTransform;

	//UINT_PTR _timer;

	HANDLE			mThreadHandle;

	WMSLocation*		m_pPickedWMSLocation;

	WMSLocation*		m_pSourceLocation;
	WMSLocation*		m_pDestLocation;

	Sky*				m_Sky;
	WarehouseRoom*		m_Room;
	bool				m_ShowSky;

	ID3DX11EffectTechnique**	mainTech;
	ID3DX11EffectTechnique**	transparentTech;


};

