#include "WPadDisplayLayout.h"
#include "Game/System/WPadHolder.h"
#include "Game/Screen/GameSceneLayoutHolder.h"

WPadDisplayLayout::WPadDisplayLayout(const char* pName) : LayoutActor(pName, false)
{
	
}

WPadDisplayLayout::~WPadDisplayLayout()
{

}

void WPadDisplayLayout::init(const JMapInfoIter& rIter)
{
	initLayoutManager("ButtonLayout", 1);

	MR::createAndAddPaneCtrl(this, "PicHiDPadL", 1);
	MR::createAndAddPaneCtrl(this, "PicHiDPadR", 1);
	MR::createAndAddPaneCtrl(this, "PicHiDPadU", 1);
	MR::createAndAddPaneCtrl(this, "PicHiDPadD", 1);
	MR::createAndAddPaneCtrl(this, "PicHiA", 1);
	MR::createAndAddPaneCtrl(this, "PicHiB", 1);
	MR::createAndAddPaneCtrl(this, "PicHiMinus", 1);
	MR::createAndAddPaneCtrl(this, "PicHiPlus", 1);
	MR::createAndAddPaneCtrl(this, "PicHi1", 1);
	MR::createAndAddPaneCtrl(this, "PicHi2", 1);
	MR::createAndAddPaneCtrl(this, "Stick", 1);
	MR::createAndAddPaneCtrl(this, "StickY", 1);
	MR::createAndAddPaneCtrl(this, "PicHiC", 1);
	MR::createAndAddPaneCtrl(this, "PicHiZ", 1);

	MR::createAndAddPaneCtrl(this, "Wiimote", 1);
	MR::createAndAddPaneCtrl(this, "PicWiiTiltBck", 1);
	MR::createAndAddPaneCtrl(this, "PicWiiPitch", 1);
	MR::createAndAddPaneCtrl(this, "Nunchuk", 1);
	MR::createAndAddPaneCtrl(this, "PicNunTiltBck", 1);
	MR::createAndAddPaneCtrl(this, "PicNunPitch", 1);

	appear();

	MR::onCalcAnim(this);
}

void WPadDisplayLayout::movement()
{
	MR::startPaneAnimAndSetFrameAndStop(this, "PicHiA", "HiA", MR::getPlayerLevelA() ? 1.f : 0.f, 0);
	MR::startPaneAnimAndSetFrameAndStop(this, "PicHiB", "HiB", MR::getPlayerLevelB() ? 1.f : 0.f, 0);
	MR::startPaneAnimAndSetFrameAndStop(this, "PicHiMinus", "HiMinus", MR::testCorePadButtonMinus(0) ? 1.f : 0.f, 0);
	MR::startPaneAnimAndSetFrameAndStop(this, "PicHiPlus", "HiPlus", MR::testCorePadButtonPlus(0) ? 1.f : 0.f, 0);
	MR::startPaneAnimAndSetFrameAndStop(this, "PicHiC", "HiC", MR::getPlayerLevelC() ? 1.f : 0.f, 0);
	MR::startPaneAnimAndSetFrameAndStop(this, "PicHiZ", "HiZ", MR::getPlayerLevelZ() ? 1.f : 0.f, 0);
	MR::startPaneAnimAndSetFrameAndStop(this, "PicHi1", "Hi1", testCorePadButton1(0) ? 1.f : 0.f, 0);
	MR::startPaneAnimAndSetFrameAndStop(this, "PicHi2", "Hi2", testCorePadButton2(0) ? 1.f : 0.f, 0);

	MR::startPaneAnimAndSetFrameAndStop(this, "PicHiDPadL", "HiDPadL", MR::testCorePadButtonLeft(0) ? 1.f : 0.f, 0);
	MR::startPaneAnimAndSetFrameAndStop(this, "PicHiDPadR", "HiDPadR", MR::testCorePadButtonRight(0) ? 1.f : 0.f, 0);
	MR::startPaneAnimAndSetFrameAndStop(this, "PicHiDPadU", "HiDPadU", MR::testCorePadButtonUp(0) ? 1.f : 0.f, 0);
	MR::startPaneAnimAndSetFrameAndStop(this, "PicHiDPadD", "HiDPadD", MR::testCorePadButtonDown(0) ? 1.f : 0.f, 0);

	MR::startPaneAnimAndSetFrameAndStop(this, "Stick", "StickX", (MR::getPlayerStickX() *50.f) + 50.f, 0);
	MR::startPaneAnimAndSetFrameAndStop(this, "StickY", "StickY", (MR::getPlayerStickY()*50.f) + 50.f, 0);

	TVec3f t1 = TVec3f();
	t1.zero();
	MR::getCorePadAcceleration(&t1, 0);
	MR::startPaneAnimAndSetFrameAndStop(this, "PicWiiTiltBck", "WiiTilt", (t1.x * -50.f) + 50.f, 0);
	MR::startPaneAnimAndSetFrameAndStop(this, "PicWiiPitch", "WiiPitch", (t1.z * -50.f) + 50.f, 0);

	t1.zero();
	MR::getSubPadAcceleration(&t1, 0);
	MR::startPaneAnimAndSetFrameAndStop(this, "PicNunTiltBck", "NunTilt", (t1.x * 50.f) + 50.f, 0);
	MR::startPaneAnimAndSetFrameAndStop(this, "PicNunPitch", "NunPitch", (t1.z * -50.f) + 50.f, 0);

	if (MR::isPaneAnimStopped(this, "Wiimote", 0) && MR::isCorePadSwing(0))
		MR::startPaneAnim(this, "Wiimote", "WiiShake", 0);

	if (MR::isPaneAnimStopped(this, "Nunchuk", 0) && MR::isSubPadSwing(0))
		MR::startPaneAnim(this, "Nunchuk", "NunShake", 0);

	LayoutActor::movement();
}


WPadDisplayObj::WPadDisplayObj(const char* pName) : LiveActor(pName)
{
	pLayout = NULL;
}

void WPadDisplayObj::init(const JMapInfoIter& rIter)
{
	pLayout = new WPadDisplayLayout("WPadDisplayLayout");
	pLayout->initWithoutIter();
}

WPadDisplayObj::~WPadDisplayObj()
{

}

namespace
{
	bool testCorePadButton1(s32 c)
	{
		return MR::getWPad(c)->mButtons->testButton1();
	}
	bool testCorePadButton2(s32 c)
	{
		return MR::getWPad(c)->mButtons->testButton2();
	}
}