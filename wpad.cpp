#include "HW/WiimoteEmu/WiimoteHid.h"
#include "HW/WiimoteEmu/WiimoteEmu.h"
#include "HW/WiimoteEmu/Attachment/Attachment.h"

#include "ControllerEmu.h"
#include "ControllerInterface/ControllerInterface.h"

using namespace std;
using namespace WiimoteEmu;

/*
const ReportFeatures reporting_mode_features[] =
{
	//0x30: Core Buttons
	{ 2, 0, 0, 0, 4 },
	//0x31: Core Buttons and Accelerometer
	{ 2, 4, 0, 0, 7 },
	//0x32: Core Buttons with 8 Extension bytes
	{ 2, 0, 0, 4, 12 },
	//0x33: Core Buttons and Accelerometer with 12 IR bytes
	{ 2, 4, 7, 0, 19 },
	//0x34: Core Buttons with 19 Extension bytes
	{ 2, 0, 0, 4, 23 },
	//0x35: Core Buttons and Accelerometer with 16 Extension Bytes
	{ 2, 4, 0, 7, 23 },
	//0x36: Core Buttons with 10 IR bytes and 9 Extension Bytes
	{ 2, 0, 4, 14, 23 },
	//0x37: Core Buttons and Accelerometer with 10 IR bytes and 6 Extension Bytes
	{ 2, 4, 7, 17, 23 },

	// UNSUPPORTED:
	//0x3d: 21 Extension Bytes
	{ 0, 0, 0, 2, 23 },
	//0x3e / 0x3f: Interleaved Core Buttons and Accelerometer with 36 IR bytes
	{ 0, 0, 0, 0, 23 },
};
*/

void test_report() {
	u8 m_reporting_mode = 0x33;

	const u8 *real_data = new u8[128];

	const ReportFeatures& real_rptf = reporting_mode_features[real_data[1] - WM_REPORT_CORE];

	//wm_ir_basic *ir = (wm_ir_basic*)(real_data + real_rptf.ir);
	//wm_ir_basic& ir = *(wm_ir_basic*&)real_data;

	//wm_ir_extended *ir[4];
	//ir[0] = (wm_ir_extended*)(real_data + real_rptf.ir);
	//ir[0]->x


	//Wiimote* wm = new Wiimote(0);
	//const std::vector<u8> &reg = ((WiimoteEmu::Attachment*)wm->m_extension->attachments[wm->m_extension->active_extension])->reg;

	/*
	ControllerEmu::Extension* ext = new ControllerEmu::Extension("ext");
	//const std::vector<u8> &reg = ((WiimoteEmu::Attachment*)ext->attachments[ext->active_extension])->reg;

	printf("%s"
		//, ext->active_extension
		, ArrayToString(&reg[0] + 0xfa + 5, 6).c_str()
		);
*/
}

/*
		PAD_LEFT =		0x01,
		PAD_RIGHT =		0x02,
		PAD_DOWN =		0x04,
		PAD_UP =		0x08,
		BUTTON_PLUS =	0x10,

		0x20
		0x40
		0x80

		BUTTON_TWO =	0x0100,
		BUTTON_ONE =	0x0200,
		BUTTON_B =		0x0400,
		BUTTON_A =		0x0800,
		BUTTON_MINUS =	 0x1000,

		?				 0x2000,
		?				 0x4000,

		BUTTON_HOME =	0x8000,
*/


/*


		z =		0x01,
		c =		0x02,

		xL =	0x04,
		xL =	0x08,

		yL =	0x10,
		yL = 0x20

*/

struct wm_core__ {
	u8 left : 1;
	u8 right : 1;
	u8 down : 1;
	u8 up : 1;
	u8 plus : 1;

	u8 : 3;

	u8 two : 1;
	u8 one : 1;
	u8 b : 1;
	u8 a : 1;
	u8 minus : 1;

	u8 : 2;

	u8 home : 1;
};

void test_ext() {
	//u8 arr[6] = { 0x09,  0xcc,  0x71,  0x79,  0x0a,  0x0a };
	//u8 arr[6] = { 0x09,  0xcc,  0x71,  0x79,  0x0a,  0x06 };
	//u8 arr[6] = { 0x09,  0xcc,  0x71,  0x79,  0x0a,  0x00 };
	//u8 arr[6] = {};

	u8 arr[7] = {};

	wm_extension &ext = *(wm_extension*)&arr[0];

	//printf("%d\n", offsetof(wm_extension, axL));

	ext.jx = 0;
	ext.jy = 0;

	ext.ax = 0;
	ext.ay = 0;
	ext.az = 0;

	//ext.axL = 0;
	//ext.bt.axL = 1;
	//ext.bt.ayL = 0;
	//ext.bt.azL = 0;

	//ext.bt.c = 1;
	//ext.bt.c = 0;
	//ext.bt.z = 0;
	//ext.bt.z = 1;

	printf(
		//"%04x\n"
		"%s\n"

		//"%04x\n"

		"jx %u\n"
		"jy %u\n"

		"x %u\n"
		"y %u\n"
		"z %u\n"

		//"c %d\n"
		//"z %d\n"

		//"xL %x\n"
		//"yL %x\n"
		//"zL %x\n"

		//, ArrayToString(arr, 6).c_str()
		, ArrayToString(arr, 7).c_str()

		, ext.jx
		, ext.jy

		, ext.ax
		, ext.ay
		, ext.az

		//, ext.bt.c
		//, ext.bt.z

		//, ext.bt.axL
		//, ext.bt.ayL
		//, ext.bt.azL
		);
}


void test_core() {
	u8 arr[4] = { 0xaa, 0xbb, 0x00, 0x60};
	u16 data = 0x0060;
	//u16 data = 0x4000;
	//u16 data = 0x4040;
	//u16 data = 0x6000;

	u16 unset = 0x20 | 0x40 | 0x80 | 0x2000 | 0x4000;
	data &= ~unset;
	//*(wm_core__*)&arr[2] &= ~unset;
	*(u16*)&arr[2] &= ~unset;

	wm_core__ c = *(wm_core__*)&data;
	printf(
		"%04x\n"
		"%s\n"

		"%04x\n"

		"left %d\n"
		"right %d\n"
		"down %d\n"
		"up %d\n"
		"plus %d\n"
		"two %d\n"
		"one %d\n"
		"b %d\n"
		"a %d\n"
		"minus %d\n"
		"home %d\n"

		, data
		, ArrayToString(arr, 4).c_str()
		, unset

		, c.left
		, c.right
		, c.down
		, c.up
		, c.plus
		, c.two
		, c.one
		, c.b
		, c.a
		, c.minus
		, c.home
		);
}


// calibration

void test_calibration() {

	ControllerEmu::AnalogStick* m_stick = new ControllerEmu::AnalogStick("");

	ControlState state[2];
	nu_cal cal;

	cal.jx.center = 126;
	cal.jx.min = 30;
	cal.jx.max = 220;

	cal.jy.center = 127;
	cal.jy.min = 31;
	cal.jy.max = 221;

	nu_js cal_js[2];

	cal_js[0] = *&cal.jx;
	cal_js[1] = *&cal.jx;

	//m_stick->GetState(&state[0], &state[1], 0, 1);

	state[0] = -1;
	state[1] = -1;

	for (int i = 0; i < 2; i++) {
		ControlState &s = *&state[i];
		nu_js c = *&cal_js[i];
		if (s < 0)
			s = s * abs(c.min - c.center) + c.center;
		else if (s > 0)
			s = s * abs(c.max - c.center) + c.center;

		printf("%d , %.2f\n", i, s);
	}
}



// wpad gekko

typedef struct vec2b_t {
	u8 x, y;
};

typedef struct joystick_t {
	struct vec2b_t max;				/**< maximum joystick values	*/
	struct vec2b_t min;				/**< minimum joystick values	*/
	struct vec2b_t center;			/**< center joystick values		*/
	struct vec2b_t pos;				/**< raw position values        */

	float ang;						/**< angle the joystick is being held		*/
	float mag;						/**< magnitude of the joystick (range 0-1)	*/
} joystick_t;

void test_calibration_gekko() {
	vec2b_t status;
	status.x = 11;
	status.y = 22;
	printf("%u %u\n", status.x, *(&status.x + 1));

	joystick_t js;

	//js.pos.x = 30;
	js.pos.x = 127;
	//js.pos.x = 128;
	//js.pos.x = 224;
	//js.pos.x = 228;
	//js.pos.x = 255;

	js.min.x = 27;
	js.center.x = 128;
	js.max.x = 255;

	//js.pos.y = 30;
	js.pos.y = 128;

	js.min.y = 30;
	js.center.y = 128;
	js.max.y = 255;

	for (int i = 0; i < 2; i++) {
		//double &s = *&js.pos.x + i;
		//nu_js c = *&cal_js[i];
		//u8 &p = *&js.pos.x;

		//u8 &p = *(&js.pos.x + 1);
		//printf("%u\n", p);

		double p = (double)*(&js.pos.x + i);
		//double &p = *(double*)(&js.pos.x + i);
		//double &p = (double&)*(&js.pos.x + i);
		//u8 &p = *(&js.pos.x + 1);
		//double &d = (double&)p;
		printf("%d: %.0f\n", i, p);

		u8 max = *(&js.max.x + i);
		u8 min = *(&js.min.x + i);
		u8 center = *(&js.center.x + i);

		double scale = double(UCHAR_MAX) / double(abs(min - max));

		if (p < center)
			//p = p * abs(min - center) + center;
			p = center - double(abs(p - center)) * (double(abs(0 - center)) / double(abs(min - center)));
		else if (p > center)
			p = double(abs(p - center)) * (double(abs(UCHAR_MAX - center)) / double(abs(max - center))) + center;
		else
			p = center;

		*(&js.pos.x + i) = u8(Common::trim8(p));

		printf("%d: %.0f"

			" , %.1f"
			" , %.1f"
			"\n\n"
			, i, p

			, double(abs(p - center))
			, scale

			);
	}

	printf("%u , %u\n",js.pos.x, js.pos.y);
}

void test_wpad() {
	//test_report();
	//test_core();
	//test_ext();
	//test_calibration();
	test_calibration_gekko();
}