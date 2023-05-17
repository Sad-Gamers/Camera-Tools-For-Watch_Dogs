#include "SadHook.h"
#include <DirectXMath.h>
using namespace DirectX;

class CameraSystem {
public:
	static void Initialize();
	static void UpdateCamera();
	static void EnableFreeCam(bool bFreeCamMode);

	//Variables for constructing a view matrix. 
	inline static float fRoll, fYaw, fPitch, fCameraFOV;
	inline static XMFLOAT3 vector3CameraPosition;
	inline static XMMATRIX matrixX, matrixY, matrixZ, matrixProduct;
	inline static XMFLOAT3X3 matrixFinalViewMatrix;

	//Variables for controlling the depth of field.
	inline static bool bLensDOFEnabled;
	inline static float bNearDOFEnabled, bFarDOFEnabled, fLensFocusRange, fLensFocalLength, fFStop;
	inline static XMFLOAT2 vector2LensConditionals;
	inline static XMFLOAT3 vector3LensFloats;

	inline static float fMovementSpeedFactor; //How fast the free cam moves, user controls this. 
	inline static bool bFreeCamMode;
};