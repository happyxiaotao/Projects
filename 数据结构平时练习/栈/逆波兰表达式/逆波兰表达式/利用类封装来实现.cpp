
enum Handle { DATA, ADD, SUB, MUL, DIV };
class Data
{
public:
	Data(Handle handle, int value)
		:m_handle(handle)
		, m_val(value)
	{}
public:
	Handle m_handle;
	char m_val;
};

//void initVector(vector<Data>& v)
//{
//	char str[maxSize];
//	cin >> str;
//	size_t str_len = strlen(str);
//	for (size_t i = 0; i < str_len; ++i)
//	{
//		switch (str[i])
//		{
//		case '+':
//			v.push_back(Data(ADD, 0));
//			break;
//		case '-':
//			v.push_back(Data(SUB, 0));
//			break;
//		case '*':
//			v.push_back(Data(MUL, 0));
//			break;
//		case '/':
//			v.push_back(Data(DIV, 0));
//			break;
//		default:
//			v.push_back(Data(DATA, str[i]));
//			break;
//		}
//	}
//}
