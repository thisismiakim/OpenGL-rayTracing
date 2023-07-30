#include "Trace.h"
#include "RGB.h"
#include "Shader.h"
#include <sstream>


const bool DEBUG = false; // 디버깅 모드 설정 true로 설정하면 디버깅 정보가 출력됨

// Phong 클래스의 생성자. 필요한 변수들을 초기화
//----------------------------------------------
Phong::Phong()
{
	CameraPos.set(0, 0, 0); // 카메라 위치 초기화
	LightColor.set(0, 0, 0); // 광원 색상 초기화
	LightDir.set(0, 0, 0); // 광원 방향 초기화
	ObjectColor.set(0, 0, 0);  // 객체 색상 초기화
	Ka = 0; Kd = 0; Ks = 0; Kp = 0; // 쉐이딩에 필요한 계수 초기화
}

// Phong 클래스의 소멸자
//----------------------------------------------
Phong::~Phong()
{
}

// 카메라 위치 설정 함수
//----------------------------------------------
void Phong::SetCamera(Point pos)
{
	CameraPos = pos;
	if (DEBUG) cout << CameraPos.print() << endl; // 디버깅 정보 출력
}

// 광원 설정 함수
//----------------------------------------------
void Phong::SetLight(RGB color, Vec3 dir)
{
	LightColor = color;
	if (DEBUG) cout << LightColor.print() << endl; // 디버깅 정보 출력
	LightDir = dir;
	LightDir.normalize(); // 광원 방향을 정규화
	if (DEBUG) cout << LightDir.print() << endl; // 디버깅 정보 출력
}


// 객체 설정 함수
//----------------------------------------------
void Phong::SetObject(RGB color, float ka, float kd, float ks, float kp)
{
	
	ObjectColor = color;
	if (DEBUG) cout << ObjectColor.print() << endl; // 디버깅 정보 출력
	Ka = ka; Kd = kd; Ks = ks; Kp = kp;  // 쉐이딩에 필요한 계수 설정
}


// 퐁 쉐이딩을 통해 그림자 생성 함수
//----------------------------------------------
void Phong::GetShade(Point point, Vec3 normal, RGB & color)
{

	// 표면의 법선 벡터를 정규화
	// Normalize surface normal
	normal.normalize();

	
	// 주변 광 계산
	// Calculate ambient term
	RGB ambient;
	ambient = LightColor;
	ambient.mult(ObjectColor);
	ambient.mult(Ka);
	if (DEBUG) cout << "ambient " << ambient.print() << endl;
	color = ambient;

	// NdotL 값 계산
	// Calculate NdotL value
	float NdotL = normal.dot(LightDir);
	if (DEBUG) cout << "NdotL " << NdotL << endl;
	if (NdotL > 0)
	{
		// 디퓨즈 계산
		// Calculate diffuse term
		RGB diffuse;
		diffuse = LightColor;
		diffuse.mult(ObjectColor);
		diffuse.mult(Kd * NdotL);
		if (DEBUG) cout << "diffuse " << diffuse.print() << endl;
		color.add(diffuse);


		// Calculate R vector
		Vec3 R = normal;
		R.mult(2 * NdotL);
		R.sub(LightDir);
		R.normalize();

		// Calculate V vector
		Vec3 V;
		float Vx = CameraPos.px - point.px;
		float Vy = CameraPos.py - point.py;
		float Vz = CameraPos.pz - point.pz;
		V.set(Vx, Vy, Vz);
		V.normalize();

		// Calculate RdotV value 
		float RdotV = R.dot(V);
		if (DEBUG) cout << "RdotV " << RdotV << endl;
		if (RdotV > 0)
		{
			// Calculate specular term
			RdotV = pow(RdotV, Kp);
			RGB specular;
			specular = LightColor;
			specular.mult(Ks * RdotV);
			if (DEBUG) cout << "specular " << specular.print() << endl;
			color.add(specular);
		}
	}
}