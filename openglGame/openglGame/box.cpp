#include "box.h"

Box::Box()
{
	// init shader
	// init model

}

void Box::Render()
{
	for (Instance& ins : intances)
	{
		model->Draw(ins, shader);
	}
}
