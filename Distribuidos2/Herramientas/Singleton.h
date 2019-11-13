#pragma once
template <class T>
class Singleton
{
	#pragma region Singleton
	protected:
		Singleton();
		static T* instancia;
		~Singleton();
	public:
		static T* getInstancia();
		static void freeInstancia();
	#pragma endregion
};
#pragma region Singleton
template <class T>
T* Singleton<T>::instancia = nullptr;
template <class T>
Singleton<T>::Singleton() {}
template <class T>
Singleton<T>::~Singleton() {}
template <class T>
T* Singleton<T>::getInstancia()
{
	if (instancia == nullptr)
		instancia = new T();
	return instancia;
}
template <class T>
void Singleton<T>::freeInstancia()
{
	if (instancia != nullptr)
		delete(instancia);
	instancia = nullptr;
}
#pragma endregion
