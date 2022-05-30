#pragma once

struct Variable {
	union data {
		int i;
		double f;
	};
	data val;
	bool isInt;

	Variable(bool type):isInt(type){}
	Variable(double ff) :isInt(0) { val.f = ff; }
	Variable(int ii) :isInt(1) { val.i = ii; }

	Variable operator+(const Variable& v) {
		if (isInt && v.isInt)
			return Variable(val.i + v.val.i);
		if (isInt) // int + float = float
			return Variable(double(val.i) + v.val.f);
		return Variable(val.f + double(v.val.i));
	}
	Variable operator-() {
		if (isInt)
			return Variable(-val.i);
		return Variable(-val.f);
	}
	Variable operator-(const Variable& v) {
		if (isInt && v.isInt)
			return Variable(val.i - v.val.i);
		if (isInt) // int - float = float
			return Variable(double(val.i) - v.val.f);
		return Variable(val.f - double(v.val.i));
	}
	Variable operator*(const Variable& v) {
		if (isInt && v.isInt)
			return Variable(val.i * v.val.i);
		if (isInt) // int * float = float
			return Variable(double(val.i) * v.val.f);
		return Variable(val.f * double(v.val.i));
	}
	Variable operator/(const Variable& v) {
		if (isInt && v.isInt) // int div int = int
			return Variable(val.i / v.val.i);
		throw - 1;
	}
	Variable operator%(const Variable& v) {
		if (isInt && v.isInt) // int % int = int
			return Variable(val.i % v.val.i);
		throw - 1;
	}
};