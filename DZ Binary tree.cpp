#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

struct Node //Структура Node для реализации элементов дерева
{
	int value;
	Node* pRight; //Указатель на правый элемент дерева
	Node* pLeft; //Указатель на левый элемент дерева
	Node* pPrev; //Указатель на предыдущий элемент дерева
};

class BSTree //Класс двоичное дерево поиска
{
private:
	Node* Root; //Указатель на корень
public:
	list <int> more_int; //Вспомогательный список со всеми элементами > value корня
	list <int> less_int; //Вспомогательный список со всеми элементами < value корня
	BSTree() //Пустой конструктор
	{
		Root = new Node;
		Root->value = 0;
		Root->pPrev = nullptr;
		Root->pRight = nullptr;
		Root->pLeft = nullptr;
	}
	BSTree(initializer_list <int> list) //Конструктор с параметром
	{
		Node* node = nullptr;
		Node* node_prev = nullptr;
		Node* subroot = nullptr;
		int flag = 1, a = 0, f = 0, g = 0;
		this->Root = new Node;
		Root->value = *list.begin();
		Root->pPrev = nullptr;
		Root->pRight = nullptr;
		Root->pLeft = nullptr;
		for (auto i : list) //Разделение переданного списка на 2 вспомогательных списка
		{
			if (a == 0) //Так как первый элемент списка и есть корень
			{
				++a;
				continue;
			}
			if (i < Root->value)
			{
				less_int.push_back(i);
			}
			if (i > Root->value)
			{
				more_int.push_back(i);
			}
		}
		while (size(less_int) != 0) //Цикл по созданию левого поддерева при помощи вспомогательного списка less_int
		{
			for (auto i : less_int)
			{
				if (f == 0) //Создания узла левого поддерева
				{
					node_prev = new Node;
					subroot = new Node;
					node_prev->value = i;
					Root->pLeft = node_prev;
					node_prev->pPrev = Root;
					node_prev->pRight = nullptr;
					node_prev->pLeft = nullptr;
					subroot = node_prev;
					less_int.pop_front();
					++f;
					break;
				}
				node_prev = subroot;
				node = new Node;
				node->value = i;
				node->pRight = nullptr;
				node->pLeft = nullptr;
				while (true) //Реализация всех узлов левого поддерева
				{
					if (i < node_prev->value)
					{
						if (node_prev->pLeft == nullptr)
						{
							node_prev->pLeft = node;
							node->pPrev = node_prev;
							break;
						}
						else
						{
							node_prev = node_prev->pLeft;
							continue;
						}
					}
					if (i > node_prev->value)
					{
						if (node_prev->pRight == nullptr)
						{
							node_prev->pRight = node;
							node->pPrev = node_prev;
							break;
						}
						else
						{
							node_prev = node_prev->pRight;
							continue;
						}
					}
				}
				less_int.pop_front(); //Удаление первого элемента списка
				break;
			}
		}
		while (size(more_int) != 0) //Цикл по созданию правого поддерева при помощи вспомогательного списка more_int
		{
			for (auto i : more_int)
			{
				if (g == 0) //Создания узла правого поддерева
				{
					node_prev = new Node;
					subroot = new Node;
					node_prev->value = i;
					Root->pRight = node_prev;
					node_prev->pPrev = Root;
					node_prev->pRight = nullptr;
					node_prev->pLeft = nullptr;
					subroot = node_prev;
					more_int.pop_front();
					++g;
					break;
				}
				node_prev = subroot;
				node = new Node;
				node->value = i;
				node->pRight = nullptr;
				node->pLeft = nullptr;
				while (true) //Реализация всех узлов правого поддерева
				{
					if (i < node_prev->value)
					{
						if (node_prev->pLeft == nullptr)
						{
							node_prev->pLeft = node;
							node->pPrev = node_prev;
							break;
						}
						else
						{
							node_prev = node_prev->pLeft;
							continue;
						}
					}
					if (i > node_prev->value)
					{
						if (node_prev->pRight == nullptr)
						{
							node_prev->pRight = node;
							node->pPrev = node_prev;
							break;
						}
						else
						{
							node_prev = node_prev->pRight;
							continue;
						}
					}
				}
				more_int.pop_front(); //Удаление первого элемента списка
				break;
			}
		}
	}
	bool add_element(int value) //Функция добавления элемента в дерево
	{
		Node* node = nullptr;
		Node* node_prev = Root;
		node = new Node;
		node->value = value;
		node->pLeft = nullptr;
		node->pRight = nullptr;
		while(true) //Цикл добавления элемента в дерево
		{
			if (node->value < node_prev->value)
			{
				if (node_prev->pLeft == nullptr)
				{
					node_prev->pLeft = node;
					node->pPrev = node_prev;
					break;
				}
				else
				{
					node_prev = node_prev->pLeft;
					continue;
				}
			}
			if (node->value > node_prev->value)
			{
				if (node_prev->pRight == nullptr)
				{
					node_prev->pRight = node;
					node->pPrev = node_prev;
					break;
				}
				else
				{
					node_prev = node_prev->pRight;
					continue;
				}
			}
		}
		return true;
	}
	bool find_element(int value) //Функция поиска элемента в дереве
	{
		Node* node_prev = Root;
		while(true) //Цикл поиска элемента в дереве
		{
			if (value < node_prev->value)
			{
				if (node_prev->pLeft == nullptr)
				{
					cout << value << " в дереве нет";
					break;
				}
				else
				{
					node_prev = node_prev->pLeft;
					continue;
				}
			}
			if (value > node_prev->value)
			{
				if (node_prev->pRight == nullptr)
				{
					cout << value << " в дереве нет";
					break;
				}
				else
				{
					node_prev = node_prev->pRight;
					continue;
				}
			}
			if(value == node_prev->value)
			{
				cout << value << " в дереве есть";
				break;
			}
		}
		return true;
	}
	bool delete_element(int value) //Функция удаления элемента из дерева по его значению value
	{
		Node* node_find = Root;
		Node* node_prev = nullptr;
		while (true) //Цикл удаления элемента из дерева
		{
			if (value < node_find->value)
			{
				if (node_find->pLeft == nullptr)
				{
					cout << value << " в дереве нет";
					break;
				}
				else
				{
					node_prev = node_find;
					node_find = node_find->pLeft;
					continue;
				}
			}
			if (value > node_find->value)
			{
				if (node_find->pRight == nullptr)
				{
					cout << value << " в дереве нет";
					break;
				}
				else
				{
					node_prev = node_find;
					node_find = node_find->pRight;
					continue;
				}
			}
			if(value == node_find->value) 
			{
				if (node_prev->pRight == node_find)
				{
					node_prev->pRight = nullptr;
				}
				if (node_prev->pLeft == node_find)
				{
					node_prev->pLeft = nullptr;
				}
				destruct(node_find); //Удаление узла и всех его потомков
				break;
			}
		}
		return true;
	}
	Node* getter_Root() //Геттер указателя корня
	{
		return Root;
	}
	void print_to_file(Node* node, ostream& stream) //Функция вывода дерева в файл
	{
		if(node != nullptr)
		{
			stream << node->value << " ";
			print_to_file(node->pLeft, stream); //Вывод левого поддерева и его потомков в файл
			print_to_file(node->pRight, stream); //Вывод правого поддерева и его потомков в файл
		}
	}
	bool save_to_file(const std::string& path) //Функция сохранения дерева в файл
	{
		ofstream fout(path);
		print_to_file(Root, fout);
		return true;
	}
	bool load_from_file(const std::string& path) //Функция загрузки дерева из файла
	{
		int a = 0, flag = 0;
		string str, temp;
		vector<string> vec_str;
		ifstream fin(path);
		getline(fin, str); //Запись дерева из файла в строку str
		for(int i = 0; i < size(str); ++i) //Разложение строки str на строчки с числами и добавление их в вектор
		{
			if (str[i] == ' ') 
			{ 
				vec_str.push_back(temp);
				temp = "";
				continue; 
			}
			temp += str[i];
		}
		for(int i = 0; i < vec_str.size(); ++i) //Преобразование каждой строчки из вектора в число и образование чисел в дерево
		{
			istringstream(vec_str[i]) >> a;
			if(flag == 0)
			{
				Root->value = a;
				++flag;
				continue;
			}
			this->add_element(a); //Добавление элемента в дерево
		}
		return true;
	}
	void print(Node* node) //Функция печати дерева в консоль
	{
		if (node != nullptr)
		{
			cout << node->value << " ";
			print(node->pLeft);
			print(node->pRight);
		}
	}
	void destruct(Node* node) //Функция удаления дерева и его поддеревьев
	{
		if(node != nullptr)
		{
			destruct(node->pLeft);
			destruct(node->pRight);
			delete node;
		}
	}
	~BSTree() //Деструктор
	{
		destruct(Root);
	}
};

int main() 
{
	setlocale(LC_ALL, "Rus"); //Реализация возможности записи русских букв
	initializer_list <int> list = { 10, 2, 12, 4, 17, 8, 3, 11, 45, 1 }; //initializer_list с начальными значениями
	BSTree Tree(list); //Создание дерева из initializer_list
	BSTree Tree_from_file;
	int x = 10, n = 0, find = 0, delete_elem = 0;
	string file_load, file_save;
	cout << "Дерево из начального списка:" << endl;
	Tree.print(Tree.getter_Root());
	cout << endl;
	while(x != 0)
	{
		cout << endl;
		cout << "Что сделать?" << endl << "0-выйти" << endl << "1-печать дерева" << endl << "2-добавление элемента" << endl << "3-найти элемент" << endl << "4-удалить элемент" << endl << "5-сохранить в файл" << endl << "6-загрузить дерево из файла" << endl;
		cin >> x;
		switch (x)
		{
		case 1:
			Tree.print(Tree.getter_Root());
			cout << endl;
			break;
		case 2:
			cout << "Какой элемент добавить?" << endl;
			cin >> n;
			Tree.add_element(n);
			break;
		case 3:
			cout << "Какой элемент найти?" << endl;
			cin >> find;
			Tree.find_element(find);
			break;
		case 4:
			cout << "Какой элемент удалить?" << endl;
			cin >> delete_elem;
			Tree.delete_element(delete_elem);
			break;
		case 5:
			cout << "В какой файл сохранить(напишите название с .txt)?" << endl;
			cin >> file_save;
			Tree.save_to_file(file_save);
			break;
		case 6:
			cout << "Из какого файла загрузить дерево(напишите название с .txt)?" << endl;
			cin >> file_load;
			Tree_from_file.load_from_file(file_load);
			cout << "Дерево из файла: ";
			Tree_from_file.print(Tree_from_file.getter_Root());
			cout << endl;
			break;
		case 0:
			break;
		}
	}
	return 0;
}