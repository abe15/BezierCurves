#include "bcomp.h"
#include <algorithm> 

	int curveCount;

	inline glm::vec3 Lerp(const glm::vec3 a, const glm::vec3 b, const float t)
	{
		glm::vec3 dest;
		dest.x = a.x + (b.x - a.x)*t;
		dest.y = a.y + (b.y - a.y)*t;
		dest.z = a.z + (b.z - a.z)*t;
		return dest;
	}

	BComp::BComp() {
		segmentPoints = new std::vector<glm::vec3>();
		controlPoints = new std::vector<glm::vec3>();
		drawingPoints = new std::vector<glm::vec3>();
		control_Points = new std::vector<glm::vec3>();
		

		segmentPoints->push_back(glm::vec3(-3,3,2));
		segmentPoints->push_back(glm::vec3(-2.5,2.5,2.5));
		segmentPoints->push_back(glm::vec3(-2,2,2.5));
		segmentPoints->push_back(glm::vec3(2,1,2.5));
		segmentPoints->push_back(glm::vec3(2,.5, .5));
		segmentPoints->push_back(glm::vec3(1.5, 1, 1));
		segmentPoints->push_back(glm::vec3(0, 1.5, .5));
		segmentPoints->push_back(glm::vec3(-1, 1, .5));
		segmentPoints->push_back(glm::vec3(-3,3,.5));
		segmentPoints->push_back(glm::vec3(-3, 3, 2));
		Interpolate(.25f);
		

		GetDrawingPoints0();
	
	}
	void BComp::GetDrawingPoints0()
	{
		
		for (int i = 0; i < controlPoints->size() - 3; i += 3)
		{
			glm::vec3 p0 = (*controlPoints)[i];
			glm::vec3 p1 = (*controlPoints)[i + 1];
			//glm::vec3 p1 = (*control_Points)[i];
			glm::vec3 p2 = (*controlPoints)[i + 2];
			//glm::vec3 p3 = (*control_Points)[i+1];
			glm::vec3 p3 = (*controlPoints)[i + 3];

			if (i == 0) //only do this for the first end point. When i != 0, this coincides with the end point of the previous segment,
			{
				(*drawingPoints).push_back(CalculateBezierPoint(0, p0, p1, p2, p3));
			}

			for (int j = 1; j <= SEGMENTS_PER_CURVE; j++)
			{
				float t = j / (float)SEGMENTS_PER_CURVE;
				(*drawingPoints).push_back(CalculateBezierPoint(t, p0, p1, p2, p3));
			}
		}

	}

	void BComp::Interpolate(float scale){
		//controlPoints

		if (segmentPoints->size() < 2)
		{
			return;
		}

		for (int i = 0; i < segmentPoints->size(); i++)
		{
			if (i == 0) // is first
			{
				glm::vec3 p1 = (*segmentPoints)[i];
				glm::vec3 p2 = (*segmentPoints)[i + 1];

				//glm::vec3 q1 = Lerp(p1, p2, scale);
				glm::vec3 tangent = (p2 - p1);
				glm::vec3 q1 = p1 + scale * tangent;

				controlPoints->push_back(p1);
				controlPoints->push_back(q1);
				control_Points->push_back(q1);
			}
			else if (i == segmentPoints->size() - 1) //last
			{
				glm::vec3 p0 =(*segmentPoints)[i - 1];
				glm::vec3 p1 = (*segmentPoints)[i];
				
				glm::vec3  q0 = p1 - scale * (p1-p0);
				
				
				controlPoints->push_back(q0);
				controlPoints->push_back(p1);
				controlPoints->push_back(q0);
				control_Points->push_back(q0);
			}
			else
			{
				glm::vec3 p0 = (*segmentPoints)[i - 1];
				glm::vec3 p1 = (*segmentPoints)[i];
				glm::vec3 p2 = (*segmentPoints)[i + 1];
				glm::vec3 tangent = normalize(p2 - p0);
				//glm::vec3 q0= Lerp(p0, p1, scale);
				//glm::vec3 q1=Lerp(p1, p2, scale);
				glm::vec3 q0 = p1 - scale*tangent * length(p1 - p0);
				glm::vec3 q1 = p1 + scale*tangent * length(p2 - p0);
				controlPoints->push_back(q0);
				controlPoints->push_back(p1);
				controlPoints->push_back(q1);
				control_Points->push_back(q0);
				control_Points->push_back(q1);
				
			}
		}

		curveCount = ((controlPoints->size()+control_Points->size()) - 1) / 3;
	}

	glm::vec3 BComp::CalculateBezierPoint(float t, glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
	{
		float u = 1 - t;
		float tt = t * t;
		float uu = u * u;
		float uuu = uu * u;
		float ttt = tt * t;

		glm::vec3 p = uuu * p0; //first term

		p += 3 * uu * t * p1; //second term
		p += 3 * u * tt * p2; //third term
		p += ttt * p3; //fourth term

		return p;

	}



	void BComp::Draw()
	{
		
		glBegin(GL_LINE_STRIP);
		glColor3f(1, 1, .5);
		for (int i = 0; i < drawingPoints->size(); i++)
		{
			glVertex3f((*drawingPoints)[i].x, (*drawingPoints)[i].y, (*drawingPoints)[i].z);			
		}
		glEnd();		
	}
	void BComp::Draw2()
	{
		
		glPointSize(10.0);
		glBegin(GL_POINTS);

		for (int i = 0; i< controlPoints->size(); i++)
		{
			glVertex3f((*controlPoints)[i].x, (*controlPoints)[i].y, (*controlPoints)[i].z);
		}
		

		glEnd();
	
	}
	void BComp::Draw3()
	{

		glPointSize(10.0);
		glBegin(GL_POINTS);
		
		for (int i = 0; i< control_Points->size(); i++)
		{
			glVertex3f((*control_Points)[i].x, (*control_Points)[i].y, (*control_Points)[i].z);
		}
		glEnd();

	}



	int BComp::getMax()
	{
			
		glm::vec3 maxEL(-1*INFINITY,-1*INFINITY,-1*INFINITY);
		int index = 0;
		for (int i = 0; i < drawingPoints->size(); i++)
		{
			glm::vec3 temp = drawingPoints->at(i);
			if (temp.x >= maxEL.x && temp.y >= maxEL.y && temp.z >= maxEL.z)
			{
				maxEL = temp;
				index = i;
			}


		}
		return index;
	
	
	}