#include "../include/utils.h"

void collide(object& A, object& B) {
    float px_1 = A.get_position().get_x();
    float py_1 = A.get_position().get_y();
    float px_2 = B.get_position().get_x();
    float py_2 = B.get_position().get_y();
    
    // move apart default instantiated objects
    // (which are created in the same position)
    if (px_1 == px_2 && py_1 == py_2) {
        px_1 -= 1.1 * (A.get_dimension() + B.get_dimension()) / 4;
        py_1 -= 1.1 * (A.get_dimension() + B.get_dimension()) / 4;
        px_2 += 1.1 * (A.get_dimension() + B.get_dimension()) / 4;
        py_2 += 1.1 * (A.get_dimension() + B.get_dimension()) / 4;
        A.set_position(vec<float>(px_1, py_1));
        B.set_position(vec<float>(px_2, py_2));
    }

    // move apart and reflect objects which overlap according
    // to their dimensions and the contact normal vector
    else if (std::sqrt(std::pow(px_1-px_2, 2) + std::pow(py_1-py_2, 2)) < (A.get_dimension() + B.get_dimension()) / 2) {
        // contact normal vector:
        //   n = r2 - r1 / abs(r2 - r1)
        // angle:
        //   φ = atan[(r2_y - r1_y) / (r2_x - r1_x)]
        // components of velocity parallel to contact normal vector swap
        // components of velocity perpendicular to contact normal vector remain unchanged
        float phi = atan2(py_2 - py_1, px_2 - px_1);

        float vx_1 = A.get_velocity().get_x();
        float vy_1 = A.get_velocity().get_y();
        float vx_2 = B.get_velocity().get_x();
        float vy_2 = B.get_velocity().get_y();

        // convert to new coordinate system
        float v_par_1 = vx_1 * std::cos(phi) + vy_1 * std::sin(phi);
        float v_per_1 = vy_1 * std::cos(phi) - vx_1 * std::sin(phi);
        float v_par_2 = vx_2 * std::cos(phi) + vy_2 * std::sin(phi);
        float v_per_2 = vy_2 * std::cos(phi) - vx_2 * std::sin(phi);

        // swap parallel components after collision
        float new_v_par_1 = v_par_2;
        float new_v_par_2 = v_par_1;
        // keep perpendicular components
        float new_v_per_1 = v_per_1;
        float new_v_per_2 = v_per_2;

        // convert back to x-y
        float new_vx_1 = new_v_par_1 * std::cos(phi) - new_v_per_1 * std::sin(phi);
        float new_vy_1 = new_v_par_1 * std::sin(phi) + new_v_per_1 * std::cos(phi);
        float new_vx_2 = new_v_par_2 * std::cos(phi) - new_v_per_2 * std::sin(phi);
        float new_vy_2 = new_v_par_2 * std::sin(phi) + new_v_per_2 * std::cos(phi);

        A.set_velocity(vec<float>(new_vx_1, new_vy_1));
        B.set_velocity(vec<float>(new_vx_2, new_vy_2));

        float factor = ((A.get_dimension() + B.get_dimension()) / 2 - std::sqrt(pow(px_2 - px_1, 2) + pow(py_2 - py_1, 2))) / 2;
        factor *= 1.01; // to make it > rather than >= for next scene::update()
        A.set_position(vec<float>(px_1 + (factor * std::cos(phi)) * (px_1>px_2?1:-1), py_1 + (factor * std::sin(phi)) * (py_1>py_2?1:-1)));
        B.set_position(vec<float>(px_2 + (factor * std::cos(phi)) * (px_1<px_2?1:-1), py_2 + (factor * std::sin(phi)) * (py_1<py_2?1:-1)));
    }
}