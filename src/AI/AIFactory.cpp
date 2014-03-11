#include "AIFactory.hpp"

using namespace AIFactory;
using std::shared_ptr;

shared_ptr<AI> AIFactory::create(const AIName name) {
	shared_ptr<AI> res;

	switch (name) {
		//TODO actual creation
	}

	return res;
}
