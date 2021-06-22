#include "Sample2.h"
#include "SampleObject.h"

namespace sample2
{
	Sample2::Sample2() : BaseScene("Sample2")
	{
		AddComponent(new mslib::object::Grid(20));
		AddComponent(new mslib::object::GameObject);
		auto camera = AddComponent(new mslib::camera::Camera);
		camera->AddComponent(new mslib::camera::CameraControlMouse);
		AddComponent(new SampleObject);
	}
	Sample2::~Sample2()
	{

	}
}