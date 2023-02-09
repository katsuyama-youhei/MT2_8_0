#include"World.h"
#include <Novice.h>

const char kWindowTitle[] = "LC1A_06_カツヤマヨウヘイ_確認課題";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	const int kWindowWidth = 1280;
	const int kWindowHeight = 720;
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	//宣言
	Vector2 kRectSize = { 80.0f,80.0f };
	Vector2 leftTopLocal = { -kRectSize.x, kRectSize.y };
	Vector2 rightTopLocal = { kRectSize.x , kRectSize.y };
	Vector2 leftBottomLocal = { -kRectSize.x , -kRectSize.y };
	Vector2 rightBottomLocal = { kRectSize.x , -kRectSize.y };

	Vector2 rectCenter = { 0.0 };
	float theta = 0.0f;

	int handle = Novice::LoadTexture("white1x1.png");

	const int speed = 10;

	Vector2 cameraPos = { 200.0f,200.0f };
	Vector2 orthoLeftTop = { -640.0f,360.0f };
	Vector2 orthoRightBottom = { 640.0f,-360.0f };
	Vector2 viewPortLeftTop = { 0.0f,0.0f };
	Vector2 viewPortSize = { kWindowWidth,kWindowHeight };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		if (keys[DIK_UP] != 0) {
			rectCenter.y += speed;
		}
		if (keys[DIK_DOWN] != 0) {
			rectCenter.y -= speed;
		}
		if (keys[DIK_LEFT] != 0) {
			rectCenter.x -= speed;
		}
		if (keys[DIK_RIGHT] != 0) {
			rectCenter.x += speed;
		}

		Matrix3x3 worldMatrix = MakeAffineMatrix(Vector2{ 1.0f,1.0f }, 0.0f, rectCenter);
		Matrix3x3 cameraMatrix = MakeAffineMatrix(Vector2{ 1.0f,1.0f }, 0.0f, cameraPos);
		Matrix3x3 viewMatrix = Inverse(cameraMatrix);
		Matrix3x3 orthoMatrix = MakeOrthographicMatrix(orthoLeftTop.x, orthoLeftTop.y, orthoRightBottom.x, orthoRightBottom.y);
		Matrix3x3 viewPortMatrix = MakeViewPortMatrix(0, 0, 1280.0f, 720.0f);

		Matrix3x3 vpMatrix = Multiply(viewMatrix, orthoMatrix);
		vpMatrix = Multiply(vpMatrix, viewPortMatrix);
		Matrix3x3 wVpMatrix = Multiply(worldMatrix, vpMatrix);


		Vector2 leftTop = Transform(leftTopLocal, wVpMatrix);
		Vector2 rightTop = Transform(rightTopLocal, wVpMatrix);
		Vector2 leftBottom = Transform(leftBottomLocal, wVpMatrix);
		Vector2 rightBottom = Transform(rightBottomLocal, wVpMatrix);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawQuad(leftTop.x, leftTop.y, rightTop.x, rightTop.y, leftBottom.x, leftBottom.y, rightBottom.x, rightBottom.y, 0, 0, 1, 1, handle, WHITE);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
