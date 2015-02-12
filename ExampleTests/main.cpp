#include <memory>

#include "../ExampleCPlusPlus/DesignPatterns/Singleton/BasicSoundSingleton/BasicSoundSingleton.h"
#include "../ExampleCPlusPlus/DesignPatterns/Singleton/AdvancedManagedSingleton/SingletonManager.h"
#include "../ExampleCPlusPlus/DesignPatterns/Singleton/AdvancedManagedSingleton/AdvancedSoundSingleton.h"
#include "../ExampleCPlusPlus/DesignPatterns/Singleton/SingletonsAsServices/SingletonServiceManager.h"
#include "../ExampleCPlusPlus/DesignPatterns/Singleton/SingletonsAsServices/SoundServiceSingleton.h"
#include "../ExampleCPlusPlus/DesignPatterns/Singleton/SingletonsAsServices/ExtendedSoundServiceSingleton.h"

#include "../ExampleCPlusPlus/DesignPatterns/State/BasicState/BasicStateMachine.h"
#include "../ExampleCPlusPlus/DesignPatterns/State/BasicState/MouseDraggingState.h"
#include "../ExampleCPlusPlus/DesignPatterns/State/BasicState/MouseScrollState.h"
#include "../ExampleCPlusPlus/DesignPatterns/State/StateStack/StateStack.h"
#include "../ExampleCPlusPlus/DesignPatterns/State/StateStack/MainMenuState.h"
#include "../ExampleCPlusPlus/DesignPatterns/State/StateStack/MapState.h"

#include "../ExampleCPlusPlus/DesignPatterns/AbstractFactory/GuiApplication.h"
#include "../ExampleCPlusPlus/DesignPatterns/AbstractFactory/PcGUIFactory.h"
#include "../ExampleCPlusPlus/DesignPatterns/AbstractFactory/MacGUIFactory.h"
#include "../ExampleCPlusPlus/DesignPatterns/Command/MoveableObject.h"
#include "../ExampleCPlusPlus/DesignPatterns/Command/CommandCoordinator.h"
#include "../ExampleCPlusPlus/DesignPatterns/Command/MoveObjectCommand.h"

#include "../ExampleCPlusPlus/DesignPatterns/EntityComponent/Component.h"
#include "../ExampleCPlusPlus/DesignPatterns/EntityComponent/Entity.h"
#include "../ExampleCPlusPlus/DesignPatterns/Observer/IObserver.h"
#include "../ExampleCPlusPlus/DesignPatterns/Observer/Subject.h"
#include "../ExampleCPlusPlus/DesignPatterns/Observer/FlexibleSubject/IFlexibleObserver.h"
#include "../ExampleCPlusPlus/DesignPatterns/Observer/FlexibleSubject/FlexibleSubject.h"
#include "../ExampleCPlusPlus/DesignPatterns/Observer/FlexibleSubject/ConcreteFlexibleObserver.h"

// :TODO: put into proper tests
int main()
{
	BasicSoundSingleton::GetInstance().PlaySound();
	BasicSoundSingleton::GetInstance().IsSoundPlaying();



	SingletonManager singletonManager;
	singletonManager.AddSingleton<AdvancedSoundSingleton>();
	AdvancedSoundSingleton::Instance().PlaySound();
	AdvancedSoundSingleton::ConstInstance().IsSoundPlaying();



	SingletonServiceManager singletonServiceManager;
	singletonServiceManager.AddSingletonService<ISoundServiceSingleton, SoundServiceSingleton>();
	singletonServiceManager.RemoveSingleton<ISoundServiceSingleton>();
	singletonServiceManager.AddSingletonService<ISoundServiceSingleton, ExtendedSoundServiceSingleton, const char*>("path//to//resources//");
	singletonServiceManager.Resolve<ISoundServiceSingleton>().PlaySound();
	singletonServiceManager.Resolve<ISoundServiceSingleton>().IsSoundPlaying();



	BasicStateMachine basicStateMachine;
	basicStateMachine.SetState<MouseDraggingState>();
	basicStateMachine.UpdateState();
	basicStateMachine.SetState<MouseScrollState>();
	basicStateMachine.UpdateState();



	StateStack stateStack;
	stateStack.PushState<MapState>();
	stateStack.UpdateState();
	stateStack.PushState<MainMenuState>();
	stateStack.UpdateState();
	stateStack.PopState();
	stateStack.UpdateState();
	stateStack.ClearStack();



	MacGUIFactory macFactory;
	PcGUIFactory pcFactory;
	GuiApplication macApp(macFactory);
	GuiApplication winApp(pcFactory);


	MoveableObject moveableObject;
	CommandCoordinator coordinator;
	coordinator.Perform(std::unique_ptr<MoveObjectCommand>(new MoveObjectCommand(moveableObject, 20, 30)));
	coordinator.Perform(std::unique_ptr<MoveObjectCommand>(new MoveObjectCommand(moveableObject, 30, 40)));
	coordinator.Perform(std::unique_ptr<MoveObjectCommand>(new MoveObjectCommand(moveableObject, 40, 50)));
	coordinator.Undo();
	coordinator.Undo();
	coordinator.Undo();
	coordinator.Redo();
	coordinator.Perform(std::unique_ptr<MoveObjectCommand>(new MoveObjectCommand(moveableObject, 100, 100)));

	

	class AnimatorComponent : public Component{public:AnimatorComponent(Entity& entity): Component(entity){}};
	Entity entity;
	Entity::CreateAndAddComponent<AnimatorComponent>(entity);
	assert(entity.HasComponent<AnimatorComponent>());
	assert(&entity.GetComponent<AnimatorComponent>());
	assert(entity.HasComponent(typeid (AnimatorComponent).hash_code()));


	class ConcreteObserver : public IObserver{ public: void Notify(const Subject&){} };
	Subject subject;
	std::shared_ptr<IObserver> observer(new ConcreteObserver);
	subject.AddObserver(observer);
	subject.Notify();
	assert(subject.HasObserver(observer));
	subject.RemoveObserver(observer);


	FlexibleSubject flexibleSubject;
	{
		ConcreteFlexibleObserver* flexibleObserver = ConcreteFlexibleObserver::Create(flexibleSubject);
		ConcreteFlexibleObserver* flexibleObserver2 = ConcreteFlexibleObserver::Create(flexibleSubject);
		flexibleSubject.Notify();
	}



	return 0;
}