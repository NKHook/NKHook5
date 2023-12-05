#include "CBasePositionableObject.h"

using namespace NKHook5::Classes;

void CBasePositionableObject::AssignParent(CBasePositionableObject* parent) {
	if(this->mParent != parent)
	{
		if(this->mParent != nullptr)
		{
			this->RemoveParent();
		}
		if(parent != nullptr)
		{
			parent->AppendChild(this);
			if(parent->mDefaultDirtyState)
			{
				this->SetDefaultDirtyState(true);
			}
		}
		this->MakeDirty();
	}
}

void CBasePositionableObject::RemoveParent()
{
	this->mParent = nullptr;
	if(!this->mDirty)
	{
		this->mDirty = true;
		auto it = ++member_list::s_iterator_to(*this);
		while(it != member_list::s_iterator_to(*this))
		{
			it->MakeDirty();
			it++;
		}
	}
	this->unlink();
}

void CBasePositionableObject::AppendChild(NKHook5::Classes::CBasePositionableObject* child)
{
	if(child != nullptr)
	{
		if(this->mDefaultDirtyState)
		{
			child->SetDefaultDirtyState(true);
		}
		if(child->mParent != nullptr)
		{
			child->RemoveParent();
		}

		child->mParent = this;
		child->MakeDirty();

		child->prev_ = this->mChildren.prev_;
		child->next_ = this->mChildren.this_ptr();
		this->mChildren.prev_ = child->this_ptr();
	}
}

void CBasePositionableObject::MakeDirty() {
	if(!this->mDirty)
	{
		this->mDirty = true;
		auto it = ++member_list::s_iterator_to(*this);
		while(it != member_list::s_iterator_to(*this))
		{
			it->MakeDirty();
			it++;
		}
	}
}