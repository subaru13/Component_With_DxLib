#include "ComponentContainer.h"

void ComponentContainer::UpdateComponents() const
{
	// �X�V����Add/Remove����悤�ɍX�V�p���X�g���R�s�[��
	// �R�s�[������X�V��������
	UpdateList copyList = mUpdateList;

	for (ComponentPtr& component : copyList)
	{
		component->Update();
	}
}
