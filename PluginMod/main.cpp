/* 
 * We assume that you need to implement a database. We need to read a single line from the command and parse it. We all know that there are different types of database commands like "INSERT", "CREATE" and so on. Now we only consider two commands, "INSERT" and "CREATE".
 * You need to read the string and store it temporarily. Then you execute the command.
 * If the command is "INSERT", then you output "This is INSERT!". If the command is "CREATE", then you read another string s and output "CREATE a string s". Here, the s is the string you input just now.
 * Please write a program decoupling as much as possible. 
 */

#include <bits/stdc++.h>

using namespace std;

class Operate {
	public:
		virtual bool execute() = 0;
};

class OperateChecker {
	public:
		function<bool(string s)> checker;
		function<Operate*(string s)> builder;
};

class OperateInsert : public Operate {
	public:
		static bool checker(string s) {
			return s == "INSERT";
		}

		static Operate* builder(string s) {
			return new OperateInsert();
		}

		static OperateChecker getChecker() {
			return (OperateChecker) {checker, builder};
		}
		
		virtual bool execute() {
			cout << "This is INSERT!" << endl;
			return true;
		}
};

class OperateCreate : public Operate {
	private:
		string text;

	public:
		OperateCreate(string s) {
			this->text = s;
		}

		static bool checker(string s) {
			return s == "CREATE";
		}

		static Operate* builder(string s) {
			string input;
			cin >> input;
			return new OperateCreate(input);
		}

		static OperateChecker getChecker() {
			return (OperateChecker) {checker, builder};
		}
		
		virtual bool execute() {
			cout << "CREATE a string " << text << endl;
			return true;
		}
};

class OperateFactory {
	private:
		vector<OperateChecker> op_type_list;

	public:
		OperateFactory() {
			loadOperateType();
		}
		bool loadOperateType() {
			// Load defualt Operate type
			return true;
		}
		bool appendOperateType(OperateChecker checker) {
			op_type_list.push_back(checker);
			return true;
		}

		Operate* getOperateFromString(string s) {
			for (size_t i = 0; i < op_type_list.size(); ++i) {
				if (op_type_list[i].checker(s)) {
					return op_type_list[i].builder(s);
				}
			}
			return nullptr;
		}

		Operate* getOperateFromCommand() {
			string s;
			getline(cin, s);
			return getOperateFromString(s);
		}
};


int main() {
	OperateFactory operateFactory;

	operateFactory.appendOperateType(OperateInsert::getChecker());
	operateFactory.appendOperateType(OperateCreate::getChecker());

	Operate *op = operateFactory.getOperateFromCommand();

	op->execute();

	return 0;
}
