#pragma once
#ifndef GDK_VECTOR_H
#define GDK_VECTOR_H


class Vector2
{
public:
	double x, y;

	Vector2() {}
	Vector2(double x, double y) 
	{
		this->x = x;
		this->y = y;
	}

	double abs() 
	{
		return sqrt(x*x + y*y);
	}
	Vector2 normalize() 
	{
		return *this / this->abs();
	}

	Vector2 operator+(Vector2 other) 
	{
		auto _x = x + other.x;
		auto _y = y + other.y;
		return Vector2(_x, _y);
	}

	Vector2 operator+=(Vector2 other) 
	{
		x += other.x;
		y += other.y;
		return *this;
	}
	
	Vector2 operator-(Vector2 other) 
	{
		auto _x = x - other.x;
		auto _y = y - other.y;
		return Vector2(_x, _y);
	}

	Vector2 operator-=(Vector2 other) 
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}
	
	Vector2 operator*(Vector2 other) 
	{
		auto _x = x * other.x;
		auto _y = y * other.y;
		return Vector2(_x, _y);
	}

	Vector2 operator*=(Vector2 other) 
	{
		x *= other.x;
		y *= other.y;
		return *this;
	}
	
	Vector2 operator*(double other) 
	{
		auto _x = x * other;
		auto _y = y * other;
		return Vector2(_x, _y);
	}

	Vector2 operator*=(double other) 
	{
		x *= other;
		y *= other;
		return *this;
	}
	
	Vector2 operator/(Vector2 other) 
	{
		auto _x = x / other.x;
		auto _y = y / other.y;
		return Vector2(_x, _y);
	}

	Vector2 operator/=(Vector2 other) 
	{
		x /= other.x;
		y /= other.y;
		return *this;
	}
	
	Vector2 operator/(double other) 
	{
		auto _x = x / other;
		auto _y = y / other;
		return Vector2(_x, _y);
	}

	Vector2 operator/=(double other) 
	{
		x /= other;
		y /= other;
		return *this;
	}

	std::string toStringA()
	{
		std::stringstream ss;
		ss << "(" << x << ", " << y << ")";
		return ss.str();
	}

	std::wstring toStringW()
	{
		std::wstringstream ss;
		ss << "(" << x << ", " << y << ")";
		return ss.str();
	}
};

class Vector3 : public Vector2 
{
public:
	double z;

	Vector3() {}
	Vector3(double x, double y, double z) 
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	double abs() 
	{
		return sqrt(x*x + y*y + z*z);
	}
	Vector3 normalize() 
	{
		return *this / this->abs();
	}

	Vector3 operator+(Vector2 other) 
	{
		Vector3 tmp = *static_cast<Vector3*>(&(*static_cast<Vector2*>(this) + other));
		tmp.z = z;
		return tmp;
	}
	Vector3 operator+(Vector3 other) 
	{
		Vector3 tmp = *static_cast<Vector3*>(&(*static_cast<Vector2*>(this) + (Vector2)other));
		tmp.z = z + other.z;
		return tmp;
	}
	
	Vector3 operator+=(Vector2 other) 
	{
		(*static_cast<Vector2*>(this) += other);
		return *this;
	}

	Vector3 operator+=(Vector3 other) 
	{
		(*static_cast<Vector2*>(this) += (Vector2)other);
		z += other.z;
		return *this;
	}
	
	Vector3 operator-(Vector2 other) 
	{
		Vector3 tmp = *static_cast<Vector3*>(&(*static_cast<Vector2*>(this) - other));
		tmp.z = z;
		return tmp;
	}

	Vector3 operator-(Vector3 other) 
	{
		Vector3 tmp = *static_cast<Vector3*>(&(*static_cast<Vector2*>(this) - (Vector2)other));
		tmp.z = z - other.z;
		return tmp;
	}
	
	Vector3 operator-=(Vector2 other) 
	{
		(*static_cast<Vector2*>(this) -= other);
		return *this;
	}

	Vector3 operator-=(Vector3 other) 
	{
		(*static_cast<Vector2*>(this) -= (Vector2)other);
		z -= other.z;
		return *this;
	}

	Vector3 operator*(Vector3 other) 
	{
		Vector3 tmp = *static_cast<Vector3*>(&(*static_cast<Vector2*>(this) * (Vector2)other));
		tmp.z = z * other.z;
		return tmp;
	}

	Vector3 operator*=(Vector3 other) 
	{
		(*static_cast<Vector2*>(this) *= (Vector2)other);
		z *= other.z;
		return *this;
	}

	Vector3 operator/(Vector3 other) 
	{
		Vector3 tmp = *static_cast<Vector3*>(&(*static_cast<Vector2*>(this) / (Vector2)other));
		tmp.z = z / other.z;
		return tmp;
	}

	Vector3 operator/=(Vector3 other) 
	{
		(*static_cast<Vector2*>(this) /= (Vector2)other);
		z /= other.z;
		return *this;
	}

	Vector3 operator*(double other)
	{
		Vector3 tmp = *(Vector3*)&((*(Vector2*)this) * other);
		tmp.z = z * other;
		return tmp;
	}

	Vector3 operator*=(double other)
	{
		(*(Vector2*)this) *= other;
		z *= other;
		return *this;
	}
	
	Vector3 operator/(double other)
	{
		Vector3 tmp = *(Vector3*)&((*(Vector2*)this) / other);
		tmp.z = z / other;
		return tmp;
	}

	Vector3 operator/=(double other)
	{
		(*(Vector2*)this) /= other;
		z /= other;
		return *this;
	}

	std::string toStringA() 
	{
		std::stringstream ss;
		ss << "(" << x << ", " << y << ", " << z << ")";
		return ss.str();
	}
	
	std::wstring toStringW() 
	{
		std::wstringstream ss;
		ss << "(" << x << ", " << y << ", " << z << ")";
		return ss.str();
	}
};

class Vector4 : public Vector3
{
public:
	double w;

	Vector4() {}
	Vector4(double x, double y, double z, double w) 
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
	
	double abs() 
	{
		return sqrt(x*x + y*y + z*z + w*w);
	}
	Vector4 normalize() 
	{
		return *this / this->abs();
	}

	Vector4 operator+(Vector2 other) 
	{
		Vector4 tmp = *static_cast<Vector4*>(&(*static_cast<Vector2*>(this) + other));
		tmp.z = z;
		tmp.w = w;
		return tmp;
	}
	
	Vector4 operator+(Vector3 other) 
	{
		Vector4 tmp = *static_cast<Vector4*>(&(*static_cast<Vector3*>(this) + other));
		tmp.w = w;
		return tmp;
	}

	Vector4 operator+(Vector4 other) 
	{
		Vector4 tmp = *static_cast<Vector4*>(&(*static_cast<Vector3*>(this) + (Vector3)other));
		tmp.w = w + other.w;
		return tmp;
	}
	
	Vector4 operator+=(Vector2 other) 
	{
		(*static_cast<Vector2*>(this) += other);
		return *this;
	}

	Vector4 operator+=(Vector3 other) 
	{
		(*static_cast<Vector3*>(this) += (Vector3)other);
		return *this;
	}
	
	Vector4 operator+=(Vector4 other) 
	{
		(*static_cast<Vector3*>(this) += (Vector3)other);
		w += other.w;
		return *this;
	}
	
	Vector4 operator-(Vector2 other) 
	{
		Vector4 tmp = *static_cast<Vector4*>(&(*static_cast<Vector3*>(this) - other));
		tmp.w = w;
		return tmp;
	}

	Vector4 operator-(Vector3 other) 
	{
		Vector4 tmp = *static_cast<Vector4*>(&(*static_cast<Vector3*>(this) - other));
		tmp.w = w;
		return tmp;
	}
	
	Vector4 operator-(Vector4 other) 
	{
		Vector4 tmp = *static_cast<Vector4*>(&(*static_cast<Vector3*>(this) - (Vector3)other));
		tmp.w = w - other.w;
		return tmp;
	}
	
	Vector4 operator-=(Vector2 other) 
	{
		(*static_cast<Vector2*>(this) -= other);
		return *this;
	}
	
	Vector4 operator-=(Vector3 other) 
	{
		(*static_cast<Vector3*>(this) -= other);
		return *this;
	}

	Vector4 operator-=(Vector4 other) 
	{
		(*static_cast<Vector3*>(this) -= (Vector3)other);
		w -= other.w;
		return *this;
	}

	Vector4 operator*(Vector4 other) 
	{
		Vector4 tmp = *static_cast<Vector4*>(&(*static_cast<Vector3*>(this) * (Vector3)other));
		tmp.w = w * other.w;
		return tmp;
	}

	Vector4 operator*=(Vector4 other) 
	{
		(*static_cast<Vector3*>(this) *= (Vector3)other);
		w *= other.w;
		return *this;
	}

	Vector4 operator/(Vector4 other) 
	{
		Vector4 tmp = *static_cast<Vector4*>(&(*static_cast<Vector3*>(this) / (Vector3)other));
		tmp.w = w / other.w;
		return tmp;
	}

	Vector4 operator/=(Vector4 other) 
	{
		(*static_cast<Vector3*>(this) /= (Vector3)other);
		w /= other.w;
		return *this;
	}

	Vector4 operator*(double other)
	{
		Vector4 tmp = *(Vector4*)&((*(Vector3*)this) * other);
		tmp.w = w * other;
		return tmp;
	}

	Vector4 operator*=(double other)
	{
		(*(Vector3*)this) *= other;
		w *= other;
		return *this;
	}

	Vector4 operator/(double other)
	{
		Vector4 tmp = *(Vector4*)&((*(Vector3*)this) / other);
		tmp.w = w / other;
		return tmp;
	}

	Vector4 operator/=(double other)
	{
		(*(Vector3*)this) /= other;
		w /= other;
		return *this;
	}

	std::string toStringA() 
	{
		std::stringstream ss;
		ss << "(" << x << ", " << y << ", " << z << ", " << w << ")";
		return ss.str();
	}
	
	std::wstring toStringW() 
	{
		std::wstringstream ss;
		ss << "(" << x << ", " << y << ", " << z << ", " << w << ")";
		return ss.str();
	}
};

class Quaternion : public Vector4
{
public:
	Quaternion() {}
	Quaternion(double x, double y, double z, double w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	Quaternion operator+(Quaternion other) 
	{
		Quaternion tmp = *static_cast<Quaternion*>(&(*static_cast<Vector4*>(this) + (Vector4)other));
		return tmp;
	}
	
	Quaternion operator+=(Quaternion other) 
	{
		*((Vector4*)this) += other;
		return *this;
	}
	
	Quaternion operator-(Quaternion other) 
	{
		Quaternion tmp = *static_cast<Quaternion*>(&(*static_cast<Vector4*>(this) - (Vector4)other));
		return tmp;
	}
	
	
	Quaternion operator-=(Quaternion other) 
	{
		*((Vector4*)this) -= (Vector4)other;
		return *this;
	}

	Quaternion operator*(Quaternion other) 
	{
		Quaternion tmp = *static_cast<Quaternion*>(&(*static_cast<Vector4*>(this) * (Vector4)other));
		return tmp;
	}

	Quaternion operator*=(Quaternion other) 
	{
		*((Vector4*)this) *= (Vector4)other;
		return *this;
	}

	Quaternion operator/(Quaternion other) 
	{
		Quaternion tmp = *static_cast<Quaternion*>(&(*static_cast<Vector4*>(this) / (Vector4)other));
		return tmp;
	}

	Quaternion operator/=(Quaternion other) 
	{
		*((Vector4*)this) /= (Vector4)other;
		return *this;
	}

	Quaternion operator*(double other)
	{
		Quaternion tmp = *(Quaternion*)&((*(Vector4*)this) * other);
		return tmp;
	}

	Quaternion operator*=(double other)
	{
		(*(Vector4*)this) *= other;
		return *this;
	}

	Quaternion operator/(double other)
	{
		Quaternion tmp = *(Quaternion*)&((*(Vector4*)this) / other);
		return tmp;
	}

	Quaternion operator/=(double other)
	{
		(*(Vector4*)this) /= other;
		return *this;
	}
};

#endif // !GDK_VECTOR_H

