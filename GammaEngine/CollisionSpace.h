#pragma once
namespace GammaEngine {
	class Collider;
	class CollisionSpace
	{
		public:
			CollisionSpace();
			~CollisionSpace();

		public:
			void Frame();
			void Add(Collider*);
			void Remove(Collider*);
		public:
			static CollisionSpace* root;
			CollisionSpace* division1;
			CollisionSpace* division2;
			CollisionSpace* division3;
			CollisionSpace* division4;
			vector<Collider*>* colliderList;
			vector<Collider*>* removeBuffer;
			float areaSize;
			vector2 center;
			int depth;
			static int maxDepth;
			static float padding;
	};
};
