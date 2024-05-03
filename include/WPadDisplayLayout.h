#pragma once

#include "syati.h"

class WPadDisplayLayout : public LayoutActor
{
public:
	WPadDisplayLayout(const char*);

	virtual void init(const JMapInfoIter& rIter);
	virtual void movement();

	~WPadDisplayLayout();
};

class WPadDisplayObj : public LiveActor
{
public:
	WPadDisplayObj(const char*);

	~WPadDisplayObj();
	virtual void init(const JMapInfoIter& rIter);

	WPadDisplayLayout* pLayout;
};

namespace
{
	bool testCorePadButton1(s32 c);
	bool testCorePadButton2(s32 c);
}