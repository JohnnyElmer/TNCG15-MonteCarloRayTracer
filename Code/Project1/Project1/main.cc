#include<iostream>
#include<fstream>
#include "color.h"
#include "vec3.h"
#include "ray.h"

#include "rtweekend.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "hittable.h"
#include "material.h"
#include "triangle.h" 


hittable_list scene_cornll_box() {
	hittable_list world;

	auto material_white = make_shared<lambertian>(color(1, 1, 1));
	auto material_red = make_shared<lambertian>(color(1, 0, 0));
	auto material_green = make_shared<lambertian>(color(0, 1, 0));
	auto material_blue = make_shared<lambertian>(color(0, 0, 1));

	auto material_yellow = make_shared<lambertian>(color(.5, .5, 0));
	auto material_orange = make_shared<lambertian>(color(.5, 0, 0.5));
	auto material_purple = make_shared<lambertian>(color(0, .5, .5));
	
	auto material_white_light = make_shared<diffuse_light>(color(15, 15, 15));
	auto material_mirror = make_shared<metal>(color(.5,.5,.5),.0005); 
	auto material_shiny = make_shared<metal>(color(.5, .5, .5), .05);
	//rummet
	//1
	world.add(make_shared<triangle>(point3(0.f, 5.f, -3.f), point3(0, -5, -3), point3(6.f, 5.f, 0.f), material_mirror)); //1
	world.add(make_shared<triangle>(point3(6.f, 5.f, 0.f), point3(0.f, -5.f, -3.f), point3(6.f, -5.f, 0.f), material_mirror)); //2

	//2
	world.add(make_shared<triangle>(point3(-6.f, 5.f, 0.f), point3(-6.f, -5.f, 0.f), point3(0.f, 5.f, -3.f), material_red)); //3
	world.add(make_shared<triangle>(point3(0.f, 5.f, -3.f), point3(-6.f, -5.f, 0.f), point3(0.f, -5.f, -3.f), material_red)); //4

	//3
	world.add(make_shared<triangle>(point3(-6.f, 5.f, 10.f), point3(-6.f, -5.f, 10.f), point3(-6.f, 5.f, 0.f), material_orange)); //5
	world.add(make_shared<triangle>(point3(-6.f, 5.f, 0.f), point3(-6.f, -5.f, 10.f), point3(-6.f, -5.f, 0.f), material_orange)); //6

	//4
	world.add(make_shared<triangle>(point3(0.f, 5.f, 13.f), point3(0, -5.f, 13.f), point3(-6.f, 5.f, 10.f), material_blue)); //7
	world.add(make_shared<triangle>(point3(-6.f, 5.f, 10.f), point3(0.f, -5.f, 13.f), point3(-6.f, -5.f, 10.f), material_blue));//8

	//5
	world.add(make_shared<triangle>(point3(6.f, 5.f, 10.f), point3(6.f, -5.f, 10.f), point3(0.f, 5.f, 13.f), material_yellow)); //9
	world.add(make_shared<triangle>(point3(0.f, 5.f, 13.f), point3(6.f, -5.f, 10.f), point3(0.f, -5.f, 13.f), material_yellow)); //10

	//6
	world.add(make_shared<triangle>(point3(6.f, 5.f, 0.f), point3(6.f, -5.f, 0.f), point3(6.f, 5.f, 10.f), material_purple)); //11
	world.add(make_shared<triangle>(point3(6.f, 5.f, 10.f), point3(6.f, -5.f, 0.f), point3(6.f, -5.f, 10.f), material_purple)); //12

   //top
	world.add(make_shared<triangle>(point3(6.0f, 5.0f, 10.0f),  point3(-6.0f, 5.0f, 10.0f), point3(0.0f, 5.0f, 13.0f), material_white));
	world.add(make_shared<triangle>(point3(-6.0f, 5.0f, 0.0f),  point3(-6.0f, 5.0f, 10.0f), point3(6.0f, 5.0f, 10.0f), material_white));
	world.add(make_shared<triangle>(point3(6.0f, 5.0f, 0.0f),   point3(-6.0f, 5.0f, 0.0f),  point3(6.0f, 5.0f, 10.0f), material_white));
	world.add(make_shared<triangle>(point3(0.0f, 5.0f, -3.0f),  point3(-6.0f, 5.0f, 0.0f),  point3(6.0f, 5.0f, 0.0f), material_white));

	//bottom
	world.add(make_shared<triangle>(point3(6.0f, -5.0f, 10.0f), point3(-6.0f, -5.0f, 10.0f), point3(0.0f, -5.0f, 13.0f), material_white));
	world.add(make_shared<triangle>(point3(-6.0f, -5.0f, 0.0f), point3(-6.0f, -5.0f, 10.0f), point3(6.0f, -5.0f, 10.0f), material_white));
	world.add(make_shared<triangle>(point3(6.0f, -5.0f, 0.0f), point3(-6.0f, -5.0f, 0.0f), point3(6.0f, -5.0f, 10.0f), material_white));
	world.add(make_shared<triangle>(point3(0.0f, -5.0f, -3.0f), point3(-6.0f, -5.0f, 0.0f), point3(6.0f, -5.0f, 0.0f), material_white));

	//top light
	world.add(make_shared<triangle>(point3(1.0f, 5.0f, 2.0f), point3(-1.0f, 5.0f, 4.0f), point3(-1.0f, 5.0f, 2.0f), material_white_light));
	world.add(make_shared<triangle>(point3(1.0f, 5.0f, 4.0f), point3(-1.0f, 5.0f, 4.0f), point3(1.0f, 5.0f, 2.0f), material_white_light));

	//tetrahedran
	//world.add(make_shared<triangle>(point3(-5.f, -5.f, 2.f), point3(-5.f, -5.f, 2.f), point3(-2.f, -5.f, 0.f), material_blue));
	//world.add(make_shared<triangle>(point3(-4.f, -5.f, 2.f), point3(0.f, -5.f, 2.f), point3(-2.f, -5.f, 4.f), material_blue));

	world.add(make_shared<triangle>(point3(-3.f, 2.f, 4.f), point3(-5.f, -5.f, 4.f), point3(-3.f, -5.f, 6.f), material_blue));
	world.add(make_shared<triangle>(point3(-3.f, 2.f, 4.f), point3(-3.f, -5.f, 6.f), point3(-1.f, -5.f, 4.f), material_blue));
	world.add(make_shared<triangle>(point3(-3.f, 2.f, 4.f), point3(-1.f, -5.f, 4.f), point3(-3.f, -5.f, 2.f), material_blue));
	world.add(make_shared<triangle>(point3(-3.f, 2.f, 4.f), point3(-3.f, -5.f, 2.f), point3(-5.f, -5.f, 4.f), material_blue));
	
	//shiny sphere
	world.add(make_shared<sphere>(point3(3, -3.5, 5), 1.f, material_green));

	//
	world.add(make_shared<sphere>(point3(3, -3.5, 3), 2.f, material_yellow));

	return world;
}


color ray_color(
	const ray& r,
	const color& background,
	const hittable& world,
	int depth
) {
	hit_record rec;

	// If we've exceeded the ray bounce limit, no more light is gathered.
	if (depth <= 0)
		return color(0, 0, 0);

	// If the ray hits nothing, return the background color.
	if (!world.hit(r, 0.001, infinity, rec)) {
		return background;
	}

	scatter_record srec;
	color emitted = rec.mat_ptr->emitted(r, rec, rec.u, rec.v, rec.p);

	if (!rec.mat_ptr->scatter(r, rec, srec))
		return emitted;

	if (srec.is_specular) {
		return srec.attenuation
			* ray_color(srec.specular_ray, background, world, depth - 1);
	}
	ray scattered;
	double pdf_v;
	
		auto on_light = point3(random_double(-1, 1), 5, random_double(2, 4));
		auto to_light = on_light - rec.p;
		auto distance_squared = to_light.length_squared();
		to_light = unit_vector(to_light);

		double light_area = (-1 - 1) * (2 - 4);
		auto light_cosine = fabs(to_light.y());

		pdf_v = distance_squared / (light_cosine * light_area);
		scattered = ray(rec.p, to_light);
	
	return emitted
		+ srec.attenuation * rec.mat_ptr->scattering_pdf(r, rec, scattered)
		* ray_color(scattered, background, world, depth - 1)
		/ pdf_v;
}

int main() {

	//Image
	const auto aspect_ratio = 16.0 / 9.0;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	const int samples_per_pixel = 256;
	const int max_depth = 10000;

	//world
	auto world = scene_cornll_box();
	
	
	//Camera
	camera cam;

	//Render
	color backg = color(.05, .05, .05);
	std::ofstream output("image.ppm", std::ofstream::binary);

	output << "P3\n" << image_width << ' ' << image_height << "\n255\n";
	std::cerr << "\nImage width: " << image_width << ' '<<"   Image height: "<<image_height << std::flush;
	for (int j = image_height - 1; j >= 0; --j) {
		std::cerr << "\nScanlines remaining:" << j << ' ' << std::flush;
		for (int i = 0; i < image_width; ++i) {
			color pixel_color(.0, .0, .0);
			for (int s = 0; s < samples_per_pixel; s++) {
				auto u = (i + random_double()) / (image_width-1);
				auto v = (j + random_double()) / (image_height-1);

				ray r = cam.get_ray(u, v);
				pixel_color += ray_color(r,backg, world, max_depth);
			}
			write_color(output, pixel_color, samples_per_pixel);
		}
	}
	std::cerr << "\nDone.\n";
	output.close();


}

// reference
//https://raytracing.github.io/books/RayTracingInOneWeekend.html 
//https://raytracing.github.io/books/RayTracingTheNextWeek.html