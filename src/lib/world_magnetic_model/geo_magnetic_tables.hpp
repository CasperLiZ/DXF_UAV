/****************************************************************************
 *
 *   Copyright (c) 2020-2022 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#include <stdint.h>

static constexpr float SAMPLING_RES = 10;
static constexpr float SAMPLING_MIN_LAT = -90;
static constexpr float SAMPLING_MAX_LAT = 90;
static constexpr float SAMPLING_MIN_LON = -180;
static constexpr float SAMPLING_MAX_LON = 180;

static constexpr int LAT_DIM = 19;
static constexpr int LON_DIM = 37;


// *INDENT-OFF*
// Magnetic declination data in radians * 10^-4
// Model: WMM-2020,
// Version: 0.5.1.11,
// Date: 2023.2959,
static constexpr const int16_t declination_table[19][37] {
	//    LONGITUDE:   -180,  -170,  -160,  -150,  -140,  -130,  -120,  -110,  -100,   -90,   -80,   -70,   -60,   -50,   -40,   -30,   -20,   -10,     0,    10,    20,    30,    40,    50,    60,    70,    80,    90,   100,   110,   120,   130,   140,   150,   160,   170,   180,
	/* LAT: -90 */ {  25968, 24223, 22477, 20732, 18987, 17241, 15496, 13751, 12005, 10260,  8515,  6770,  5024,  3279,  1534,  -212, -1957, -3702, -5447, -7193, -8938,-10683,-12429,-14174,-15919,-17665,-19410,-21155,-22901,-24646,-26391,-28137,-29882, 31204, 29459, 27713, 25968, },
	/* LAT: -80 */ {  22532, 20403, 18465, 16692, 15053, 13515, 12052, 10641,  9266,  7916,  6584,  5266,  3957,  2652,  1345,    25, -1317, -2690, -4101, -5554, -7050, -8588,-10167,-11787,-13453,-15172,-16959,-18832,-20816,-22935,-25210,-27645,-30214, 29980, 27364, 24861, 22532, },
	/* LAT: -70 */ {  14982, 13582, 12455, 11491, 10620,  9787,  8944,  8056,  7103,  6083,  5013,  3921,  2836,  1782,   761,  -249, -1286, -2394, -3598, -4901, -6284, -7717, -9167,-10610,-12037,-13454,-14884,-16372,-17999,-19918,-22449,-26262, 30651, 24118, 19620, 16853, 14982, },
	/* LAT: -60 */ {   8437,  8188,  7904,  7627,  7370,  7114,  6804,  6369,  5753,  4931,  3930,  2818,  1700,   675,  -202,  -957, -1685, -2510, -3519, -4723, -6060, -7433, -8756, -9967,-11031,-11929,-12644,-13138,-13309,-12861,-10754, -3446,  4976,  7697,  8456,  8576,  8437, },
	/* LAT: -50 */ {   5498,  5533,  5475,  5383,  5307,  5268,  5231,  5102,  4757,  4091,  3078,  1804,   465,  -710, -1572, -2128, -2520, -2962, -3656, -4682, -5937, -7220, -8363, -9262, -9856,-10090, -9889, -9125, -7611, -5245, -2337,   411,  2522,  3947,  4821,  5295,  5498, },
	/* LAT: -40 */ {   3964,  4056,  4062,  4015,  3953,  3917,  3921,  3908,  3733,  3195,  2168,   722,  -840, -2147, -3000, -3441, -3615, -3671, -3847, -4436, -5431, -6515, -7399, -7931, -8029, -7642, -6743, -5355, -3646, -1948,  -492,   728,  1773,  2641,  3300,  3732,  3964, },
	/* LAT: -30 */ {   2991,  3077,  3105,  3088,  3027,  2947,  2885,  2851,  2723,  2241,  1199,  -326, -1932, -3177, -3905, -4241, -4310, -4089, -3653, -3451, -3841, -4600, -5294, -5634, -5498, -4901, -3935, -2730, -1530,  -592,    81,   680,  1306,  1913,  2426,  2791,  2991, },
	/* LAT: -20 */ {   2349,  2394,  2409,  2408,  2363,  2266,  2156,  2079,  1933,  1434,   370, -1125, -2601, -3652, -4172, -4277, -4064, -3495, -2629, -1844, -1591, -1961, -2612, -3073, -3100, -2733, -2094, -1281,  -512,   -31,   227,   527,   971,  1455,  1882,  2193,  2349, },
	/* LAT: -10 */ {   1955,  1949,  1924,  1918,  1887,  1800,  1687,  1594,  1409,   855,  -213, -1594, -2863, -3681, -3934, -3694, -3111, -2326, -1481,  -733,  -278,  -324,  -801, -1304, -1511, -1416, -1100,  -604,  -112,   122,   165,   323,   697,  1141,  1541,  1833,  1955, },
	/* LAT:   0 */ {   1742,  1708,  1649,  1637,  1623,  1551,  1442,  1326,  1071,   449,  -595, -1823, -2871, -3446, -3431, -2921, -2150, -1370,  -721,  -188,   221,   325,    39,  -378,  -629,  -683,  -585,  -325,   -39,    44,   -23,    63,   408,   858,  1284,  1609,  1742, },
	/* LAT:  10 */ {   1604,  1611,  1567,  1580,  1603,  1551,  1425,  1235,   859,   141,  -880, -1954, -2774, -3103, -2888, -2275, -1498,  -789,  -278,   101,   424,   569,   401,    79,  -153,  -261,  -287,  -210,  -109,  -155,  -300,  -275,    30,   491,   978,  1391,  1604, },
	/* LAT:  20 */ {   1415,  1564,  1623,  1713,  1798,  1775,  1616,  1312,   767,   -88, -1129, -2076, -2665, -2766, -2432, -1826, -1115,  -468,   -11,   296,   554,   697,   602,   358,   161,    41,   -54,  -124,  -208,  -401,  -642,  -701,  -464,   -11,   535,  1056,  1415, },
	/* LAT:  30 */ {   1108,  1474,  1734,  1957,  2116,  2125,  1936,  1512,   784,  -242, -1355, -2225, -2633, -2565, -2163, -1582,  -927,  -310,   150,   453,   683,   827,   804,   654,   506,   380,   217,     0,  -288,  -666, -1036, -1195, -1032,  -603,   -24,   587,  1108, },
	/* LAT:  40 */ {    743,  1328,  1823,  2217,  2466,  2510,  2294,  1761,   852,  -371, -1602, -2461, -2775, -2620, -2173, -1580,  -927,  -298,   210,   573,   841,  1037,  1128,  1116,  1040,   890,   615,   196,  -349,  -958, -1479, -1721, -1601, -1183,  -585,    86,   743, },
	/* LAT:  50 */ {    444,  1189,  1871,  2431,  2800,  2909,  2682,  2031,   895,  -593, -2005, -2912, -3203, -3010, -2520, -1874, -1165,  -468,   147,   651,  1067,  1420,  1697,  1865,  1882,  1691,  1238,   519,  -382, -1286, -1961, -2243, -2116, -1675, -1043,  -316,   444, },
	/* LAT:  60 */ {    235,  1085,  1891,  2590,  3099,  3318,  3111,  2309,   810, -1131, -2834, -3810, -4063, -3805, -3235, -2491, -1666,  -827,   -20,   729,  1420,  2049,  2589,  2981,  3136,  2942,  2291,  1161,  -262, -1580, -2442, -2745, -2579, -2088, -1402,  -609,   235, },
	/* LAT:  70 */ {    -24,   907,  1804,  2605,  3225,  3527,  3291,  2188,     3, -2663, -4605, -5440, -5462, -4988, -4226, -3296, -2276, -1213,  -140,   918,  1942,  2906,  3772,  4476,  4918,  4941,  4316,  2821,   608, -1502, -2793, -3232, -3074, -2547, -1806,  -944,   -24, },
	/* LAT:  80 */ {   -810,   110,   960,  1651,  2041,  1882,   762, -1679, -4737, -6845, -7642, -7558, -6962, -6067, -4992, -3805, -2547, -1247,    74,  1398,  2711,  3992,  5219,  6359,  7357,  8118,  8461,  8005,  6022,  2124, -1542, -3249, -3597, -3259, -2579, -1730,  -810, },
	/* LAT:  90 */ { -29553,-27808,-26062,-24317,-22572,-20826,-19081,-17336,-15590,-13845,-12100,-10355, -8610, -6864, -5119, -3374, -1629,   116,  1861,  3607,  5352,  7097,  8842, 10588, 12333, 14078, 15824, 17569, 19315, 21060, 22806, 24551, 26297, 28042, 29788,-31299,-29553, },
};

// Magnetic inclination data in radians * 10^-4
// Model: WMM-2020,
// Version: 0.5.1.11,
// Date: 2023.2959,
static constexpr const int16_t inclination_table[19][37] {
	//    LONGITUDE:   -180,  -170,  -160,  -150,  -140,  -130,  -120,  -110,  -100,   -90,   -80,   -70,   -60,   -50,   -40,   -30,   -20,   -10,     0,    10,    20,    30,    40,    50,    60,    70,    80,    90,   100,   110,   120,   130,   140,   150,   160,   170,   180,
	/* LAT: -90 */ { -12567,-12567,-12567,-12567,-12567,-12567,-12567,-12567,-12567,-12567,-12567,-12567,-12567,-12567,-12567,-12567,-12567,-12567,-12567,-12567,-12567,-12567,-12567,-12567,-12567,-12567,-12567,-12567,-12567,-12567,-12567,-12567,-12567,-12567,-12567,-12567,-12567, },
	/* LAT: -80 */ { -13650,-13516,-13356,-13175,-12982,-12780,-12577,-12377,-12186,-12010,-11854,-11719,-11609,-11523,-11460,-11418,-11398,-11400,-11427,-11482,-11565,-11680,-11825,-11999,-12197,-12415,-12644,-12877,-13105,-13317,-13504,-13653,-13757,-13807,-13804,-13749,-13650, },
	/* LAT: -70 */ { -14098,-13779,-13460,-13137,-12806,-12462,-12107,-11751,-11408,-11100,-10848,-10666,-10554,-10502,-10487,-10490,-10496,-10504,-10526,-10582,-10690,-10866,-11113,-11429,-11802,-12221,-12669,-13134,-13600,-14052,-14469,-14813,-14999,-14943,-14712,-14414,-14098, },
	/* LAT: -60 */ { -13514,-13160,-12821,-12488,-12145,-11773,-11358,-10904,-10437,-10008, -9680, -9507, -9506, -9643, -9847,-10037,-10158,-10198,-10182,-10166,-10214,-10375,-10667,-11078,-11579,-12136,-12723,-13319,-13908,-14469,-14966,-15255,-15075,-14689,-14282,-13888,-13514, },
	/* LAT: -50 */ { -12494,-12151,-11819,-11497,-11174,-10827,-10428, -9957, -9428, -8909, -8522, -8401, -8607, -9070, -9633,-10140,-10494,-10650,-10613,-10457,-10315,-10324,-10550,-10972,-11517,-12110,-12697,-13234,-13679,-13976,-14083,-14010,-13806,-13522,-13193,-12845,-12494, },
	/* LAT: -40 */ { -11239,-10889,-10541,-10195, -9856, -9518, -9158, -8733, -8213, -7650, -7229, -7195, -7663, -8490, -9411,-10236,-10889,-11316,-11445,-11268,-10922,-10654,-10654,-10943,-11409,-11914,-12357,-12676,-12833,-12837,-12748,-12612,-12434,-12202,-11915,-11587,-11239, },
	/* LAT: -30 */ {  -9602, -9221, -8839, -8448, -8056, -7682, -7327, -6938, -6426, -5816, -5370, -5465, -6248, -7457, -8706, -9796,-10704,-11406,-11793,-11770,-11390,-10882,-10555,-10563,-10819,-11141,-11394,-11503,-11438,-11263,-11090,-10959,-10816,-10610,-10329, -9982, -9602, },
	/* LAT: -20 */ {  -7373, -6928, -6507, -6077, -5633, -5204, -4816, -4406, -3842, -3158, -2719, -2997, -4126, -5748, -7373, -8733, -9789,-10554,-10980,-11002,-10629,-10010, -9455, -9218, -9271, -9434, -9573, -9586, -9412, -9141, -8950, -8869, -8770, -8565, -8249, -7835, -7373, },
	/* LAT: -10 */ {  -4418, -3875, -3416, -2977, -2519, -2070, -1659, -1210,  -588,   111,   463,    15, -1335, -3264, -5235, -6829, -7909, -8529, -8783, -8710, -8290, -7598, -6935, -6596, -6560, -6654, -6769, -6790, -6600, -6305, -6156, -6175, -6143, -5931, -5548, -5017, -4418, },
	/* LAT:   0 */ {   -910,  -278,   193,   598,  1017,  1433,  1820,  2257,  2834,  3405,  3596,  3082,  1767,  -156, -2196, -3829, -4818, -5232, -5281, -5102, -4652, -3927, -3222, -2857, -2798, -2866, -2989, -3060, -2930, -2697, -2649, -2804, -2879, -2698, -2273, -1639,  -910, },
	/* LAT:  10 */ {   2558,  3192,  3631,  3974,  4330,  4696,  5045,  5426,  5870,  6234,  6261,  5759,  4661,  3086,  1397,    37,  -751,  -984,  -884,  -642,  -223,   422,  1055,  1389,  1452,  1411,  1313,  1222,  1263,  1364,  1282,  1003,   800,   867,  1219,  1826,  2558, },
	/* LAT:  20 */ {   5414,  5947,  6330,  6627,  6941,  7283,  7624,  7966,  8294,  8488,  8394,  7923,  7078,  5978,  4854,  3955,  3438,  3330,  3487,  3735,  4070,  4540,  5000,  5254,  5312,  5298,  5252,  5194,  5181,  5159,  4980,  4639,  4333,  4240,  4412,  4838,  5414, },
	/* LAT:  30 */ {   7568,  7943,  8262,  8546,  8855,  9201,  9557,  9895, 10167, 10276, 10126,  9700,  9068,  8355,  7697,  7191,  6907,  6872,  7019,  7233,  7483,  7785,  8074,  8248,  8306,  8322,  8326,  8316,  8292,  8206,  7981,  7623,  7263,  7041,  7025,  7221,  7568, },
	/* LAT:  40 */ {   9266,  9487,  9743, 10029, 10355, 10715, 11081, 11418, 11667, 11746, 11593, 11231, 10758, 10285,  9892,  9612,  9467,  9467,  9581,  9745,  9922, 10108, 10280, 10405, 10484, 10546, 10603, 10636, 10618, 10505, 10260,  9907,  9538,  9252,  9110,  9122,  9266, },
	/* LAT:  50 */ {  10802, 10923, 11124, 11393, 11715, 12068, 12421, 12736, 12955, 13013, 12872, 12575, 12211, 11867, 11594, 11409, 11319, 11318, 11387, 11492, 11607, 11724, 11841, 11957, 12076, 12200, 12314, 12386, 12375, 12248, 12000, 11671, 11331, 11046, 10856, 10776, 10802, },
	/* LAT:  60 */ {  12319, 12391, 12540, 12757, 13026, 13325, 13626, 13891, 14066, 14094, 13959, 13711, 13423, 13153, 12933, 12778, 12689, 12659, 12677, 12726, 12795, 12881, 12988, 13120, 13280, 13457, 13622, 13730, 13734, 13611, 13385, 13106, 12828, 12592, 12421, 12329, 12319, },
	/* LAT:  70 */ {  13757, 13799, 13892, 14032, 14210, 14413, 14620, 14800, 14905, 14888, 14753, 14553, 14337, 14134, 13961, 13827, 13733, 13679, 13661, 13674, 13717, 13790, 13894, 14031, 14199, 14386, 14570, 14710, 14755, 14681, 14519, 14320, 14126, 13961, 13840, 13771, 13757, },
	/* LAT:  80 */ {  14994, 15005, 15042, 15100, 15175, 15259, 15336, 15382, 15367, 15292, 15182, 15060, 14938, 14825, 14725, 14644, 14582, 14541, 14523, 14527, 14554, 14604, 14676, 14769, 14881, 15008, 15143, 15276, 15383, 15427, 15386, 15297, 15201, 15115, 15050, 15009, 14994, },
	/* LAT:  90 */ {  15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, },
};

// Magnetic strength data in milli-Gauss * 10
// Model: WMM-2020,
// Version: 0.5.1.11,
// Date: 2023.2959,
static constexpr const int16_t strength_table[19][37] {
	//    LONGITUDE:  -180, -170, -160, -150, -140, -130, -120, -110, -100,  -90,  -80,  -70,  -60,  -50,  -40,  -30,  -20,  -10,    0,   10,   20,   30,   40,   50,   60,   70,   80,   90,  100,  110,  120,  130,  140,  150,  160,  170,  180,
	/* LAT: -90 */ {  5447, 5447, 5447, 5447, 5447, 5447, 5447, 5447, 5447, 5447, 5447, 5447, 5447, 5447, 5447, 5447, 5447, 5447, 5447, 5447, 5447, 5447, 5447, 5447, 5447, 5447, 5447, 5447, 5447, 5447, 5447, 5447, 5447, 5447, 5447, 5447, 5447, },
	/* LAT: -80 */ {  6053, 5989, 5910, 5818, 5715, 5603, 5485, 5363, 5240, 5121, 5006, 4901, 4808, 4728, 4665, 4621, 4597, 4595, 4616, 4663, 4734, 4828, 4943, 5075, 5219, 5369, 5519, 5662, 5793, 5907, 5999, 6068, 6112, 6131, 6126, 6100, 6053, },
	/* LAT: -70 */ {  6298, 6164, 6013, 5848, 5669, 5476, 5271, 5056, 4837, 4622, 4420, 4238, 4080, 3950, 3846, 3769, 3723, 3710, 3740, 3816, 3945, 4126, 4355, 4623, 4919, 5226, 5530, 5814, 6064, 6267, 6418, 6513, 6554, 6546, 6496, 6411, 6298, },
	/* LAT: -60 */ {  6184, 5991, 5788, 5579, 5359, 5124, 4868, 4589, 4297, 4008, 3741, 3515, 3336, 3202, 3103, 3029, 2979, 2959, 2986, 3077, 3247, 3499, 3827, 4214, 4637, 5072, 5493, 5877, 6201, 6449, 6612, 6690, 6691, 6627, 6513, 6361, 6184, },
	/* LAT: -50 */ {  5841, 5611, 5378, 5146, 4913, 4668, 4397, 4094, 3765, 3434, 3132, 2893, 2733, 2642, 2594, 2559, 2525, 2498, 2503, 2576, 2752, 3044, 3442, 3915, 4423, 4929, 5403, 5821, 6160, 6401, 6538, 6578, 6535, 6424, 6261, 6062, 5841, },
	/* LAT: -40 */ {  5391, 5145, 4899, 4659, 4424, 4186, 3932, 3647, 3333, 3008, 2709, 2488, 2372, 2347, 2366, 2386, 2390, 2377, 2363, 2393, 2526, 2804, 3225, 3741, 4288, 4812, 5278, 5665, 5956, 6143, 6231, 6233, 6163, 6031, 5850, 5631, 5391, },
	/* LAT: -30 */ {  4877, 4636, 4396, 4161, 3934, 3715, 3496, 3265, 3009, 2733, 2476, 2295, 2226, 2251, 2318, 2389, 2454, 2502, 2523, 2534, 2604, 2807, 3173, 3664, 4196, 4692, 5108, 5423, 5625, 5725, 5751, 5724, 5644, 5511, 5331, 5114, 4877, },
	/* LAT: -20 */ {  4320, 4107, 3897, 3692, 3496, 3313, 3145, 2981, 2803, 2604, 2413, 2281, 2241, 2286, 2376, 2486, 2614, 2741, 2827, 2861, 2887, 2986, 3230, 3617, 4069, 4495, 4841, 5074, 5178, 5185, 5155, 5108, 5026, 4898, 4731, 4534, 4320, },
	/* LAT: -10 */ {  3790, 3628, 3475, 3328, 3192, 3072, 2968, 2876, 2778, 2663, 2541, 2442, 2398, 2424, 2512, 2642, 2797, 2955, 3076, 3137, 3151, 3179, 3306, 3561, 3888, 4210, 4473, 4634, 4668, 4615, 4548, 4484, 4396, 4272, 4122, 3958, 3790, },
	/* LAT:   0 */ {  3412, 3318, 3234, 3161, 3105, 3067, 3040, 3021, 2996, 2947, 2868, 2774, 2694, 2665, 2709, 2813, 2945, 3080, 3194, 3268, 3299, 3321, 3398, 3557, 3767, 3981, 4160, 4265, 4270, 4202, 4114, 4022, 3910, 3779, 3645, 3520, 3412, },
	/* LAT:  10 */ {  3282, 3251, 3230, 3226, 3250, 3297, 3352, 3404, 3438, 3428, 3359, 3245, 3119, 3026, 3001, 3044, 3125, 3224, 3324, 3409, 3472, 3535, 3624, 3743, 3879, 4018, 4138, 4208, 4209, 4147, 4036, 3893, 3731, 3572, 3436, 3339, 3282, },
	/* LAT:  20 */ {  3399, 3401, 3427, 3480, 3571, 3692, 3820, 3936, 4016, 4028, 3955, 3813, 3647, 3509, 3435, 3424, 3460, 3533, 3630, 3728, 3819, 3918, 4029, 4141, 4251, 4363, 4465, 4531, 4541, 4481, 4344, 4141, 3913, 3703, 3540, 3439, 3399, },
	/* LAT:  30 */ {  3722, 3728, 3781, 3880, 4022, 4192, 4367, 4523, 4631, 4657, 4584, 4429, 4241, 4078, 3975, 3930, 3935, 3986, 4074, 4173, 4271, 4377, 4494, 4612, 4732, 4859, 4980, 5067, 5092, 5033, 4876, 4636, 4361, 4107, 3907, 3778, 3722, },
	/* LAT:  40 */ {  4222, 4218, 4282, 4404, 4570, 4757, 4940, 5096, 5201, 5227, 5159, 5011, 4825, 4653, 4526, 4451, 4427, 4450, 4511, 4591, 4678, 4776, 4891, 5025, 5176, 5338, 5490, 5600, 5638, 5582, 5426, 5187, 4913, 4654, 4443, 4297, 4222, },
	/* LAT:  50 */ {  4832, 4822, 4876, 4985, 5130, 5289, 5439, 5560, 5634, 5644, 5581, 5455, 5293, 5131, 4994, 4898, 4844, 4833, 4859, 4909, 4979, 5071, 5190, 5340, 5516, 5700, 5866, 5984, 6026, 5981, 5850, 5654, 5430, 5215, 5035, 4904, 4832, },
	/* LAT:  60 */ {  5392, 5378, 5404, 5465, 5550, 5644, 5731, 5798, 5832, 5824, 5771, 5678, 5558, 5430, 5312, 5217, 5151, 5118, 5116, 5144, 5201, 5288, 5406, 5554, 5720, 5888, 6035, 6138, 6181, 6158, 6075, 5950, 5804, 5662, 5540, 5448, 5392, },
	/* LAT:  70 */ {  5726, 5705, 5700, 5711, 5733, 5759, 5783, 5798, 5798, 5780, 5742, 5685, 5616, 5540, 5467, 5403, 5356, 5328, 5324, 5344, 5389, 5459, 5551, 5659, 5776, 5890, 5989, 6061, 6100, 6103, 6074, 6021, 5954, 5884, 5819, 5765, 5726, },
	/* LAT:  80 */ {  5790, 5772, 5757, 5744, 5734, 5725, 5715, 5703, 5689, 5671, 5649, 5624, 5598, 5571, 5547, 5527, 5513, 5508, 5513, 5529, 5555, 5590, 5633, 5681, 5730, 5778, 5821, 5855, 5879, 5892, 5894, 5887, 5872, 5853, 5832, 5810, 5790, },
	/* LAT:  90 */ {  5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, },
};
