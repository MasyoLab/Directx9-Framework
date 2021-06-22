#include "Sample1.h"
#include "SampleObject.h"

namespace sample1
{
	Sample1::Sample1() : BaseScene("Sample1")
	{
		AddComponent(new mslib::object::Grid(20));
		AddComponent(new mslib::object::GameObject);
		auto camera = AddComponent(new mslib::camera::Camera);
		camera->AddComponent(new mslib::camera::CameraControlMouse);
		AddComponent(new SampleObject);
	}
	Sample1::~Sample1()
	{

	}
}