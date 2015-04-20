
#ifndef _OBJECT_H
#define _OBJECT_H

class tObject
{
	//private:
	//	string tag;

	public:
		tObject(void);
		virtual ~tObject(void) {}

		virtual void GeometryPass(tRenderer *) {};
		virtual void ForwardPass(tRenderer *) {};
		virtual tBoundingBox GetBoundingBox(void) = 0;

		virtual void AddedToWorld(tWorld *world) {};
		virtual void RemovedFromWorld(tWorld *world) {};


		//void SetTag(string tag)		{ this->tag = tag; }
		//string GetTag(void)			{ return tag; }
};

class tTransformObject : public tObject
{
	protected:
		tTransform transform;

		virtual void TransformChanged(void) {}

	public:
		tTransformObject(void)						{ this->transform = tTransform::GetIdentity(); }
		tTransformObject(tTransform transform)		{ this->transform = transform; }

		tTransform GetTransform(void)				{ return transform; }
		void SetTransform(tTransform transform);
};


#endif
