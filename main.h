#pragma once

#include <iostream>
#include <map>
#include <cmath>

#include <Common/Common.h>
#include <Common/Thread.h>
#include <lzo/lzo1x.h>
#include <Common/FileUtil.h>
#include <Common/IniFile.h>

#include <wx/wx.h>

#include "libogc.h"

using namespace std;

double Round(double n, double dec);
void DrawCoordinate(wxPen p, wxBrush b, int x, int y);

void test_lzop();
void test_ini();
void test_wx(int argc, char **argv);
//void test_wx(int argc, wchar_t **argv);
void test_debug();
void test_wpad();
void test_gcpad();
void test_thread();