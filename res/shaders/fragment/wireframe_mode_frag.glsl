// fragment

#version 150 core

out vec4 FragColor;

const float PHI = 1.61803398874989484820459; // golden ratio

float gold_noise(in float range) {
    static float seed = 1;

    float result = fract(tan(distance(xy * PHI, xy) * seed) * range);

    seed += 0.1;

    return result;
}

void main() {
    FragColor = vec4(gold_noise(1.0), gold_noise(1.0), gold_noise(1.0), 1.0);
}
