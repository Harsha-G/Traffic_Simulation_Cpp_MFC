#pragma once
#include <string>

using namespace std;

enum color { red, yellow, green };
enum traj { east = 0, north = 90, west = 180, south = 270 };
enum turn_opt { turn_opt_leftrightstraight, turn_opt_leftstraight, turn_opt_rightstraight, turn_opt_leftright, turn_opt_left, turn_opt_right };
enum turn { LEFT, RIGHT, STRAIGHT };

string return_str_color(color col);
string return_str_dir(traj dir);