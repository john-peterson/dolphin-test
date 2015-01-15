#include "main.h"

#include <wx/artprov.h>
#include <wx/wx.h>

//extern wxMemoryDC dc;

u8 __pad_clampregion[8] = {30, 180, 15, 72, 40, 15, 59, 31};

void polygon_vertex(int stick) {
	// polygon offset
	double max
		, diagonal
		//, box = 64
		, box = 256
		, d_of = box / 256.0
		//, x_of = box / 2.0
		, x_of = 0
		;

	if (stick == 0)
	{
		//max = (87.0 / 127.0) * 100;
		//diagonal = (55.0 / 127.0) * 100.0;
		max = 72 + 15;
		diagonal = 40 + 15;
	}
	else if (stick == 1)
	{
		max = (74.0 / 127.0) * 100;
		diagonal = (46.0 / 127.0) * 100;
	}
	else
	{
		//max = (82.0 / 127.0) * 100;
		//diagonal = (58.0 / 127.0) * 100;
		max = 127;
		diagonal = 100;
	}

	// polygon corners
	wxPoint Points[8];
	Points[0].x = (int)(0.0 * d_of + x_of); Points[0].y = (int)(max * d_of + x_of);
	Points[1].x = (int)(diagonal * d_of + x_of); Points[1].y = (int)(diagonal * d_of + x_of);
	Points[2].x = (int)(max * d_of + x_of); Points[2].y = (int)(0.0 * d_of + x_of);
	Points[3].x = (int)(diagonal * d_of + x_of); Points[3].y = (int)(-diagonal * d_of + x_of);
	Points[4].x = (int)(0.0 * d_of + x_of); Points[4].y = (int)(-max * d_of + x_of);
	Points[5].x = (int)(-diagonal * d_of + x_of); Points[5].y = (int)(-diagonal * d_of + x_of);
	Points[6].x = (int)(-max * d_of + x_of); Points[6].y = (int)(0.0 * d_of + x_of);
	Points[7].x = (int)(-diagonal * d_of + x_of); Points[7].y = (int)(diagonal * d_of + x_of);

	for (int i = 0; i < 8; i++) {
		//printf("%d %d\n", Points[i].x - 128, Points[i].y - 128);
		printf("%d %d\n", Points[i].x, Points[i].y);
	}
}

void test_outer() {
	PADStatus s;

	int x = 0, y = 0;
	for (int j = 0; j < 4; j++) {
		for (int k = SCHAR_MIN; k <= SCHAR_MAX; k++) {
			switch (j) {
			case 0:
			s.stickX = k;
			s.stickY = SCHAR_MAX;
				break;

			case 1:
			s.stickX = SCHAR_MAX;
			s.stickY = k;
				break;

			case 2:
			s.stickX = k;
			s.stickY = SCHAR_MIN;
				break;

			case 3:
			s.stickX = SCHAR_MIN;
			s.stickY = k;
				break;
			}

			//status[i].substickX = j;
			//status[i].substickY = 0;

			x = s.stickX, y = s.stickY;

			// 72, 40, 15
			__pad_clampstick(&s.stickX,&s.stickY,__pad_clampregion[3],__pad_clampregion[4],__pad_clampregion[2]);

			// 59, 31, 15
			__pad_clampstick(&s.substickX,&s.substickY,__pad_clampregion[6],__pad_clampregion[7],__pad_clampregion[5]);
			printf("%d %4d , %4d [%4d]%s %4d [%4d]%s\n", j, k
				, x, s.stickX
				, abs(s.stickX) < __pad_clampregion[3] ? " " : "*"

				, y, s.stickY
				, abs(s.stickY) < __pad_clampregion[3] ? " " : "*"
				);
		}
	}
}

void test_vertical() {
	PADStatus s;

	int x = 0, y = 0;
	for (int k = SCHAR_MIN; k <= SCHAR_MAX; k++) {

		s.stickX = 0;
		s.stickY = k;
		//status[i].substickX = 0;
		//status[i].substickY = k;

		x = s.stickX, y = s.stickY;

		// 72, 40, 15
		__pad_clampstick(&s.stickX,&s.stickY,__pad_clampregion[3],__pad_clampregion[4],__pad_clampregion[2]);

		// 59, 31, 15
		__pad_clampstick(&s.substickX,&s.substickY,__pad_clampregion[6],__pad_clampregion[7],__pad_clampregion[5]);
		printf("%4d , %4d [%4d]%s %4d [%4d]%s\n"
			, k

			, x, s.stickX
			, abs(s.stickX) < __pad_clampregion[3] ? " " : "*"

			, y, s.stickY
			, abs(s.stickY) < __pad_clampregion[3] ? " " : "*"
			);
	}
}

void test_circle() {
	 //FILE *pFile = fopen("pad.txt","w");

	PADStatus s;
	double x = 0, y = 0;
	double radius = 128;

	for (double i = 0; i <= 2 * M_PI; i += 0.01) {
		s8 x = radius * cos(i);
		s8 y = radius * sin(i);
		s.stickX = x;
		s.stickY = y;

		// 72, 40, 15
		__pad_clampstick(&s.stickX, &s.stickY, __pad_clampregion[3], __pad_clampregion[4], __pad_clampregion[2]);

		// 59, 31, 15
		//__pad_clampstick(&s.substickX, &s.substickY, __pad_clampregion[6], __pad_clampregion[7], __pad_clampregion[5]);

		/*
		fprintf(pFile,
			"%0.2f"
			", %d [%d] %d [%d]"
			"\n"
			, i
			, x, s.stickX
			, y, s.stickY
			);
		*/

		DrawCoordinate(*wxGREEN_PEN, *wxGREEN_BRUSH, x, y);
		DrawCoordinate(*wxBLUE_PEN, *wxBLUE_BRUSH, s.stickX, s.stickY);
	}
	//fflush(pFile);
}

void test_area() {
	 FILE *pFile = fopen("pad.txt","w");

	PADStatus s;
	double x = 0, y = 0;

	for (int x = SCHAR_MIN; x <= SCHAR_MAX; x++) {
		for (int y = SCHAR_MIN; y <= SCHAR_MAX; y++) {
			s.stickX = x;
			s.stickY = y;
			//status[i].substickX = 0;
			//status[i].substickY = k;

			// 72, 40, 15
			__pad_clampstick(&s.stickX, &s.stickY, __pad_clampregion[3], __pad_clampregion[4], __pad_clampregion[2]);

			// 59, 31, 15
			//__pad_clampstick(&s.substickX, &s.substickY, __pad_clampregion[6], __pad_clampregion[7], __pad_clampregion[5]);

			double a = atan2(y, x);
			double ac = atan2(s.stickY, s.stickX);
			double r = sqrt(x*x + y*y);
			double rc = sqrt(s.stickX*s.stickX + s.stickY*s.stickY);

			a = Round(a, 3);

			fprintf(pFile,
				"%0.2f"
				", %4.0f [%4.0f] %d [%d] %d [%d]"
				"\n"
				, a
				, r, rc
				, x, s.stickX
				, y, s.stickY
				);

			if (abs(x - s.stickX) > 15 || abs(y - s.stickY) > 15) {
				//DrawCoordinate(*wxBLUE_PEN, *wxBLUE_BRUSH, s.stickX, s.stickY);
				DrawCoordinate(*wxRED_PEN, *wxRED_BRUSH, x, y);
			}
		}
	}

	fflush(pFile);
}

void test_octagon() {
	double vertices = 8;
	double radius = 72;
	double centerX = 0, centerY = 0;

	//if(radius <= 0 || vertices < 3)
	//  return NULL;

	//Polygon* poly = new Polygon;

	double angle = 2.0 * M_PI / vertices;

	for(int i = 0; i < vertices; i++) {
		double a = (angle * i);
		double x = centerX + radius * cos(a);
		double y = centerY + radius * sin(a);
		printf("%2.1f , %2.1f , %2.0f %2.0f\n", angle, a, x, y);
		//poly->add(centerX + radius * cos(a), centerY + radius * sin(a));
	}
}

struct coordinate {
	s32 x;
	s32 y;
};

s32 main_coordinate[6][2] = {
	{-15, 87}
	, {15, 87}
	, {55, 55}
	, {87, 15}
	, {87, -15}
	, {-55, -55}
};

void test_clamp() {
	PADStatus s;
	for (int i = 0; i < 6; i++) {
		s.stickX = main_coordinate[i][0];
		s.stickY = main_coordinate[i][1];
		__pad_clampstick(&s.stickX, &s.stickY, __pad_clampregion[3], __pad_clampregion[4], __pad_clampregion[2]);
		printf("%d , %d[%d] %d[%d]\n"
			, i
			, main_coordinate[i][0], s.stickX
			, main_coordinate[i][1], s.stickY
		);
	}
}


void test_gcpad() {
	//test_octagon();
	//test_clamp();

	//polygon_vertex(0);

	//test_outer();
	//test_vertical();
	test_area();
	test_circle();

	// outer
}