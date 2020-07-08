#pragma once
#include "pch.h"
#include "../Patches/FlagHacker.h"
#ifdef _DEBUG
#define _DEBUG_WAS_DEFINED
#undef _DEBUG
#endif
#include "../../../packages/python.3.9.0-b4/tools/include/Python.h"
#ifdef _DEBUG_WAS_DEFINED
#define _DEBUG
#undef _DEBUG_WAS_DEFINED
#endif
#include "PyMain.h"
#include <thread>
#include <filesystem>
#include <iostream>

void addFlag(PyObject* name, PyObject* flag) {
	const char* name_chrs = PyBytes_AsString(name);
	string* name_str = new string(name_chrs);

	long flag_long = PyLong_AsLong(flag);

	FlagHacker::addHackedFlag(name_str, flag_long);
}

PyMethodDef nkhook5_methods[] = {
	// The first property is the name exposed to Python, fast_tanh, the second is the C++
	// function name that contains the implementation.
	{ "addFlag", (PyCFunction)addFlag, METH_O, nullptr },

	// Terminate the array with an object containing nulls.
	{ nullptr, nullptr, 0, nullptr }
};

PyModuleDef nkhook5_module = {
	PyModuleDef_HEAD_INIT,
	"nkhook5",
	"NKHook5 api for Python",
	0,
	nkhook5_methods
};

namespace fs = std::filesystem;

void PyMain::setupPython()
{
	Py_Initialize();
	PyModule_Create(&nkhook5_module);

	string appdata = string(getenv("APPDATA"));
	string nkhookdata = appdata.append("/NKHook5");
	string plugins = nkhookdata.append("/Plugins");

	for (const auto& entry : fs::directory_iterator(plugins)) {
		string ext = entry.path().extension().u8string();
		if (ext.compare(".py")==0) {
			cout << entry.path().u8string() << endl;
		}
	}
}
