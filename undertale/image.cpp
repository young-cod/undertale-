#include "stdafx.h"
#include "Image.h"

/********************************************************************************
## Image ##
@@ ID2D1Bitmap* bitmap : ImageManager���� ������ ��Ʈ��
@@ TagLoadImageInfo loadinfo : �̹��� ����(Ű��,���� ���)

�������̹����� �ƴ� �̹��� Ŭ���� ����
*********************************************************************************/
Image::Image(ID2D1Bitmap * const bitmap, const TagLoadedImageInfo & loadinfo)
	:mBitmap(bitmap), mLoadInfo(loadinfo), mScale(1.f), mAlpha(1.f), mAngle(0.f), mMaxFrameX(1), mMaxFrameY(1)
{
	this->mSize.x = (float)this->mBitmap->GetPixelSize().width;
	this->mSize.y = (float)this->mBitmap->GetPixelSize().height;

	FrameRect rc;
	rc.x = 0;
	rc.y = 0;
	rc.width = mSize.x;
	rc.height = mSize.y;
	count = 0;
	this->mFrameInfo.push_back(rc);
	this->ResetRenderOption();
}
/********************************************************************************
## Image ##
@@ ID2D1Bitmap* bitmap : ImageManager���� ������ ��Ʈ��
@@ TagLoadImageInfo loadinfo : �̹��� ����(Ű��,���� ���)
@@ int maxFrameX : ���� ������ ��
@@ int maxFrameY : ���� ������ ��

������ �̹��� Ŭ���� ����
*********************************************************************************/
Image::Image(ID2D1Bitmap *const bitmap, const TagLoadedImageInfo & loadinfo, const int  maxFrameX, const int  maxFrameY)
	:mBitmap(bitmap), mLoadInfo(loadinfo), mMaxFrameX(maxFrameX), mMaxFrameY(maxFrameY), mScale(1.f), mAlpha(1.f), mAngle(0.f)
{
	this->mSize.x = (float)mBitmap->GetPixelSize().width;
	this->mSize.y = (float)mBitmap->GetPixelSize().height;

	float frameX = mSize.x / (float)this->mMaxFrameX;
	float frameY = mSize.y / (float)this->mMaxFrameY;

	mFrame = 0;

	FrameRect rc;
	for (int j = 0; j < maxFrameY; ++j)
	{
		for (int i = 0; i < maxFrameX; ++i)
		{
			rc.x = (float)i * (frameX);
			rc.y = (float)j * (frameY);
			rc.width = frameX;
			rc.height = frameY;
			count = 0;
			this->mFrameInfo.push_back(rc);
		}
	}

	this->ResetRenderOption();
}
/********************************************************************************
## ~Image ##
��Ʈ�� ����
*********************************************************************************/
Image::~Image()
{
	NEW_SAFE_RELEASE(mBitmap);
}
/********************************************************************************
## PerfeactRender ##
@@�⺻������ x,y���� �Է�@@
@@������ left, top ����@@
*********************************************************************************/
void Image::Render(const float X, const float Y, const float scaleW, const float scalseH,
	const float degreeAngle, const float rotateX, const float rotateY,
	const float transX, const float transY)
{
	//RECT rect = rc;

	//������ ����� ������ش�
	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(scaleW, scalseH, D2D1::Point2F(X, Y));
	//ȸ�� ����� ������ش�. 
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(degreeAngle, D2D1::Point2F(X + rotateX, Y + rotateY));
	//�̵� ����� ������ش�.
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(transX, transY);

	D2D1_RECT_F dxArea = D2D1::RectF(X, Y, X + mSize.x, Y + mSize.y);

	D2DRenderer::GetInstance()->GetRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * translateMatrix);
	D2DRenderer::GetInstance()->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, mAlpha);
	ResetRenderOption();
}
void Image::barRender(const float X, const float Y, const float sourX)
{

	D2D1_RECT_F dxArea = D2D1::RectF(X, Y, X + sourX, Y + mSize.y);
	D2D1_RECT_F dxArea2 = D2D1::RectF(X, Y, X + mSize.x, Y + mSize.y);

	D2DRenderer::GetInstance()->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, mAlpha);
	ResetRenderOption();
}

void Image::bulletRender(const float X, const float Y, const float degreeAngle, const float rotateX, const float rotateY)
{
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(degreeAngle, D2D1::Point2F(X + rotateX, Y + rotateY));


	float cameraX = X - CAMERAMANAGER->getX();
	float cameraY = Y - CAMERAMANAGER->getY();

	D2D1_RECT_F dxArea = D2D1::RectF((cameraX), (cameraY), (cameraX)+mSize.x, (cameraY)+mSize.y);

	//D2DRenderer::GetInstance()->GetRenderTarget()->SetTransform(rotateMatrix);
	D2DRenderer::GetInstance()->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, mAlpha);
	ResetRenderOption();
}
void Image::mapRender(const float X, const float Y)
{
	float cameraX = X - CAMERAMANAGER->getX();
	float cameraY = Y - CAMERAMANAGER->getY();

	D2D1_RECT_F dxArea = D2D1::RectF(cameraX, cameraY, cameraX	+ mSize.x, cameraY + mSize.y);

	D2DRenderer::GetInstance()->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, mAlpha);
	ResetRenderOption();
}

/********************************************************************************
## PerfeactFrameRender ##
*********************************************************************************/
void Image::FrameRender(const float X, const float Y, const int frameX, const int frameY, const float alpha,
	const float scaleW, const float scalseH,
	const float degreeAngle, const float rotateX, const float rotateY,
	const float transX, const float transY)
{
	float cameraX = 0, cameraY = 0;

	cameraX = X - CAMERAMANAGER->getX();
	cameraY = Y - CAMERAMANAGER->getY();

	//���� �������ε��� 
	int frame = frameY * mMaxFrameX + frameX;
	Vector2 size = mSize * mScale;

	/*D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(degreeAngle, D2D1::Point2F(X + rotateX,Y + rotateY));
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(transX, transY);*/

	//�׸� ���� ���� 
	D2D1_RECT_F dxArea = D2D1::RectF(cameraX, cameraY, cameraX + mSize.x, cameraY + mSize.y);
	D2D1_RECT_F dxSrc = D2D1::RectF((float)mFrameInfo[frame].x, (float)mFrameInfo[frame].y,
		(float)(mFrameInfo[frame].x + mFrameInfo[frame].width),
		(float)(mFrameInfo[frame].y + mFrameInfo[frame].height));
	//������� ����
	//D2DRenderer::GetInstance()->GetRenderTarget()->SetTransform( rotateMatrix * translateMatrix);

	D2DRenderer::GetInstance()->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, alpha,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, &dxSrc);

	if (mAlpha <= 0)this->ResetRenderOption();
}
void Image::bossFrameRender(const float X, const float Y, const int frameX, const int frameY,
	const float scaleW, const float scalseH,
	const float degreeAngle, const float rotateX, const float rotateY,
	const float transX, const float transY)
{

	//���� �������ε��� 
	int frame = frameY * mMaxFrameX + frameX;
	Vector2 size = mSize * mScale;

	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(degreeAngle, D2D1::Point2F(X + rotateX, Y + rotateY));
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(transX, transY);

	//�׸� ���� ���� 
	D2D1_RECT_F dxArea = D2D1::RectF(X, Y, X + mSize.x, Y + mSize.y);
	D2D1_RECT_F dxSrc = D2D1::RectF((float)mFrameInfo[frame].x, (float)mFrameInfo[frame].y,
		(float)(mFrameInfo[frame].x + mFrameInfo[frame].width),
		(float)(mFrameInfo[frame].y + mFrameInfo[frame].height));
	//������� ����
	D2DRenderer::GetInstance()->GetRenderTarget()->SetTransform(rotateMatrix * translateMatrix);

	//������ ��û
	//mAlpha -= 0.01f;
	D2DRenderer::GetInstance()->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, mAlpha,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, &dxSrc);

	if (mAlpha <= 0)this->ResetRenderOption();
}

void Image::autoFrameRender(const float X, const float Y, const int frameX, const int frameY,
	const int speed, const bool loop,
	const float scaleW, const float scalseH,
	const float degreeAngle, const float rotateX, const float rotateY,
	const float transX, const float transY)
{

	//���� �������ε��� 
	count++;
	if (count%speed == 0)
	{
		mFrame++;
		if (mFrame >= mMaxFrameX && loop)mFrame = 0;
		else if (mFrame >= mMaxFrameX && !loop)mFrame = mMaxFrameX - 1;
		count = 0;
	}

	Vector2 size = mSize * mScale;

	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(degreeAngle, D2D1::Point2F(X + rotateX, Y + rotateY));
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(transX, transY);

	//�׸� ���� ���� 
	D2D1_RECT_F dxArea = D2D1::RectF(X, Y, X + mSize.x, Y + mSize.y);
	D2D1_RECT_F dxSrc = D2D1::RectF((float)mFrameInfo[mFrame].x, (float)mFrameInfo[mFrame].y,
		(float)(mFrameInfo[mFrame].x + mFrameInfo[mFrame].width),
		(float)(mFrameInfo[mFrame].y + mFrameInfo[mFrame].height));
	//������� ����
	D2DRenderer::GetInstance()->GetRenderTarget()->SetTransform(rotateMatrix * translateMatrix);

	//������ ��û
	//mAlpha -= 0.01f;
	D2DRenderer::GetInstance()->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, mAlpha,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, &dxSrc);

	if (mAlpha <= 0)this->ResetRenderOption();
}

/********************************************************************************
## ResetRenderOption ##
�̹��� Ŭ���� ���� ���� �ɼǵ� ���� �ʱ�ȭ
*********************************************************************************/
void Image::ResetRenderOption()
{
	this->mAlpha = 1.0f;
	this->mScale = 1.0f;
	this->mAngle = 0.f;
	if (mFrameInfo.size() <= 1)
	{
		this->mSize.x = (float)mBitmap->GetPixelSize().width;
		this->mSize.y = (float)mBitmap->GetPixelSize().height;
	}
	else
	{
		this->mSize.x = mFrameInfo[0].width;
		this->mSize.y = mFrameInfo[0].height;
	}
}
