
#if !defined(MYLIB_CONSTANTS_H)


const int a = 100;
const int b = 0x7f;

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <iostream>

const glm::vec3 emerald_amb(0.0215f, 0.1745f, 0.0215f);
const glm::vec3 emerald_diff(0.07568f, 0.61424, 0.07568);
const glm::vec3 emerald_spec(0.633, 0.727811, 0.633);
const float emerald_shine = 128 * 0.6;



const glm::vec3 jade_amb(0.135, 0.2225, 0.1575);
const glm::vec3 jade_diff(0.54, 0.89, 0.63);
const glm::vec3 jade_spec(0.316228, 0.316228, 0.316228);
const float jade_shine = 128 * 0.1;

const glm::vec3 obsidian_amb(.05375, .05, .06625);
const glm::vec3 obsidian_diff(.18275, .17, .22525);
const glm::vec3 obsidian_spec(0.332741, 0.328634, 0.346435);
const float obsidian_shine = 128 * 0.3;

const glm::vec3 pearl_amb(0.25, 0.20725, 0.20725);
const glm::vec3 pearl_diff(1, 0.829, 0.829);
const glm::vec3 pearl_spec(0.296648, 0.296648, 0.296648);
const float pearl_shine = 128 * 0.088;


const glm::vec3 ruby_amb(0.1745, 0.01175, 0.01175);
const glm::vec3 ruby_diff(0.61424, 0.04136, 0.04136);
const glm::vec3 ruby_spec(0.727811, 0.626959, 0.626959);
const float ruby_shine = 128 * 0.6;

const glm::vec3 turquoise_amb(0.1, 0.18725, 0.1745);
const glm::vec3 turquoise_diff(0.396, 0.74151, 0.69102);
const glm::vec3 turquoise_spec(0.297254, 0.30829, 0.306678);
const float turquoise_shine = 128 * 0.1;


const glm::vec3 brass_amb(0.329412, 0.223529, 0.027451);
const glm::vec3 brass_diff(0.780392, 0.568627, 0.113725);
const glm::vec3 brass_spec(0.992157, 0.941176, 0.807843);
const float brass_shine = 128 * 0.21794872;

const glm::vec3 bronze_amb(0.2125, 0.1275, 0.054);
const glm::vec3 bronze_diff(0.714, 0.4284, 0.18144);
const glm::vec3 bronze_spec(0.393548, 0.271906, 0.166721);
const float bronze_shine = 128 * 0.2;


const glm::vec3 chrome_amb(0.25, 0.25, 0.25);
const glm::vec3 chrome_diff(0.4, 0.4, 0.4);
const glm::vec3 chrome_spec(0.774597, 0.774597, 0.774597);
const float chrome_shine = 128 * 0.6;


const glm::vec3 copper_amb(0.19125, 0.0735, 0.0225);
const glm::vec3 copper_diff(0.7038, 0.27048, 0.0828);
const glm::vec3 copper_spec(0.256777, 0.137622, 0.086014);
const float copper_shine = 128 * 0.1;

const glm::vec3 gold_amb(0.24725, 0.1995, 0.0745);
const glm::vec3 gold_diff(0.75164, 0.60648, 0.22648);
const glm::vec3 gold_spec(0.628281, 0.137622, 0.137622);
const float gold_shine = 128 * 0.1;

const glm::vec3 silver_amb(0.19225, 0.19225, 0.19225);
const glm::vec3 silver_diff(0.50754, 0.50754, 0.50754);
const glm::vec3 silver_spec(0.508273, 0.508273, 0.508273);
const float silver_shine = 128 * 0.4;


const glm::vec3 black_plastic_amb(0.0, 0.0, 0.0);
const glm::vec3 black_plastic_diff(0.01, 0.01, 0.01);
const glm::vec3 black_plastic_spec(0.50, 0.50, 0.50);
const float black_plastic_shine = 128 * 0.25;


const glm::vec3 cyan_plastic_amb(0.0, 0.1, 0.06);
const glm::vec3 cyan_plastic_diff(0.0, 0.50980392, 0.50980392);
const glm::vec3 cyan_plastic_spec(0.50980392, 0.50980392, 0.50980392);
const float cyan_plastic_shine = 128 * 0.25;


const glm::vec3 green_plastic_amb(0.0, 0.0, 0.0);
const glm::vec3 green_plastic_diff(0.01, 0.01, 0.01);
const glm::vec3 green_plastic_spec(0.50, 0.50, 0.50);
const float green_plastic_shine = 128 * 0.25;


const glm::vec3 red_plastic_amb(0.0, 0.0, 0.0);
const glm::vec3 red_plastic_diff(0.01, 0.35, 0.01);
const glm::vec3 red_plastic_spec(0.45, 0.55, 0.45);
const float red_plastic_shine = 128 * 0.25;

const glm::vec3 white_plastic_amb(0.0, 0.0, 0.0);
const glm::vec3 white_plastic_diff(0.55, 0.55, 0.55);
const glm::vec3 white_plastic_spec(0.70, 0.70, 0.70);
const float white_plastic_shine = 128 * 0.25;

const glm::vec3 yellow_plastic_amb(0.0, 0.0, 0.0);
const glm::vec3 yellow_plastic_diff(0.5, 0.5, 0.0);
const glm::vec3 yellow_plastic_spec(0.60, 0.60, 0.50);
const float yellow_plastic_shine = 128 * 0.25;


const glm::vec3 black_rubber_amb(0.02, 0.02, 0.02);
const glm::vec3 black_rubber_diff(0.01, 0.01, 0.01);
const glm::vec3 black_rubber_spec(0.4, 0.4, 0.4);
const float black_rubber_shine = 128 * .078125;

const glm::vec3 cyan_rubber_amb(0.0, 0.05, 0.05);
const glm::vec3 cyan_rubber_diff(0.4, 0.5, 0.5);
const glm::vec3 cyan_rubber_spec(0.04, 0.7, 0.7);
const float cyan_rubber_shine = 128 * .078125;

const glm::vec3 green_rubber_amb(0.0, 0.05, 0.0);
const glm::vec3 green_rubber_diff(0.4, 0.5, 0.4);
const glm::vec3 green_rubber_spec(0.04, 0.7, 0.04);
const float green_rubber_shine = 128 * .078125;


const glm::vec3 red_rubber_amb(0.05, 0.0, 0.0);
const glm::vec3 red_rubber_diff(0.5, 0.4, 0.4);
const glm::vec3 red_rubber_spec(0.7, 0.04, 0.04);
const float red_rubber_shine = 128 * .078125;
#endif
