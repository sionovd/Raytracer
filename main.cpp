
#include "utils.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include "color.h"
#include "camera.h"
#include <iostream>
#include <fstream>
#include <chrono>


color ray_color(const ray& r, const hittable& world, int depth) {
	hit_record rec;

	// If we've exceeded the ray bounce limit, no more light is gathered.
	if (depth <= 0)
		return color(0, 0, 0);

	if (world.hit(r, 0.001, infinity, rec)) {
		ray scattered;
		color attenuation;
		if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
			return attenuation * ray_color(scattered, world, depth - 1);
		return color(0, 0, 0);
	}
	vec3 unit_direction{ unit_vector(r.direction()) };
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

void progress_bar(double progress)
{
	int bar_width{ 70 };
	std::cout << "[";
	auto pos = bar_width * progress;
	for (int i = 0; i < bar_width; ++i) {
		if (i < pos) std::cout << "=";
		else if (i == pos) std::cout << ">";
		else std::cout << " ";
	}
	std::cout << "] " << int(progress * 100.0) << " %\r";
	std::cout.flush();
}

int main()
{
	auto begin = std::chrono::steady_clock::now();

	// Image
	const double aspect_ratio{ 16.0 / 9.0 };
	const long long image_width{ 400 };
	const long long image_height{ static_cast<long long>(image_width / aspect_ratio) };
	const int samples_per_pixel{ 10 };
	const int max_depth{ 50 };

	// World
	auto material_ground = std::make_shared<lambertian>(color{ 0.8, 0.8, 0.0 });
	auto material_center = std::make_shared<lambertian>(color{ 0.7, 0.3, 0.3 });
	auto material_left = std::make_shared<metal>(color{ 0.8, 0.8, 0.8 }, 0.3);
	auto material_right = std::make_shared<metal>(color{ 0.8, 0.6, 0.2 }, 0.1);

	hittable_list world;
	world.add(std::make_shared<sphere>(point3{ 0.0, -100.5, -1.0 }, 100.0, material_ground));
	world.add(std::make_shared<sphere>(point3{ 0.0, 0.0, -1.0 }, 0.5, material_center));
	world.add(std::make_shared<sphere>(point3{ -1.0, 0.0, -1.0 }, 0.5, material_left));
	world.add(std::make_shared<sphere>(point3{ 1.0, 0.0, -1.0 }, 0.5, material_right));

	// Camera
	auto viewport_height = 2.0;
	auto viewport_width = aspect_ratio * viewport_height;
	auto focal_length = 1.0;
	camera cam(viewport_height, viewport_width, focal_length);

	// Render
	std::ofstream myfile;
	myfile.open("image.ppm");
	myfile << "P3\n" << image_width << ' ' << image_height << "\n255\n";
	
	for (int j = image_height - 1; j >= 0; --j) {
		progress_bar(double(image_height - j) / image_height);
		for (int i = 0; i < image_width; ++i) {
			color pixel_color{ 0, 0, 0 };
			for (int s = 0; s < samples_per_pixel; ++s) {
				auto u = (i + random_double()) / (image_width - 1);
				auto v = (j + random_double()) / (image_height - 1);
				ray r{ cam.get_ray(u, v) };
				pixel_color += ray_color(r, world, max_depth);
			}
			write_color(myfile, pixel_color, samples_per_pixel);
			
		}
	}
	myfile.close();
	auto end = std::chrono::steady_clock::now();
	std::cout << '\n';
	std::cout << "Time to render: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 1000.0 << "[s]";

}