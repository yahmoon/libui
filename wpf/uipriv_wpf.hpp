// 25 november 2015
#include <vcclr.h>
#include "../ui.h"
#include "ui_wpf.hpp"
#include "../common/uipriv.h"
#include "unmanaged.h"

#using <System.dll>
#using <WindowsBase.dll>
#using <PresentationCore.dll>
#using <PresentationFramework.dll>
using namespace System;
using namespace System::ComponentModel;
using namespace System::Windows;
using namespace System::Windows::Controls;

// text.cpp
extern String ^fromUTF8(const char *);

// control.cpp
extern UIElement ^genericHandle(uiControl *c);
