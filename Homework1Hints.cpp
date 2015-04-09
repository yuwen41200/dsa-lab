// OOP Homework1: Big Number Operations - Hints
// by Y.W.Pu, Dept. of C.S., NCTU

/*
	在開始之前…
	先認識一下 friend 關鍵字：
		在函式前加上 friend，表示要將該函式「加為好友」
		該函式並不是該 class 的 member function，卻可以直接存取該 class 的 private member
	那什麼是 static？
		靜態成員不屬於任何一個物件，是整個 class 共享的，不需要建立物件就可以直接存取
		e.g. ClassName::staticDataMember, ClassName::staticMemberFunction(params)
		小心 static member function 並沒有 this 指標，也就不能直接存取非 static 的成員
	C++ 的字串（string）資料型別：
		C 要使用 char[] 或 char* 來存放字串，這種字串我們叫做 C-string
		C++ 直接支援 string 型別，只要先引入 <string> 即可
		C++ 的 string 其實是一個 class，已經幫你寫好很多建構函式（constructor）、operator overload……等等
*/

// 將 int 轉換成 C-string
	sprintf(cstr, "%d", a); // 記得要引入 <cstdio> 或 <stdio.h>
// 將 C-string 轉換成 string
	string str = cstr; // 或 str(cstr)，兩者皆會呼叫 string 的建構函式 string(const char*)
// 取得 string 的長度
	int len = str.length() // 或 str.size()，兩者是完全相同的
// 將兩個 string 串接在一起
	string str3 = str1 + str2;
// 將 string 轉換成 C-string
	char *cstr = str.c_str();

/*
	其實寫這題不一定會用到這些，只是在我的作法裡有用到，就順便講一下囉
*/

/*
	以下，正文開始
	大數 class 的定義：
		number[] 用來存放大數，一個位置存放一位數字，預設所有位置都是 0
		positive 為 true 表示其為正數（預設值），false 表示負數
		length 存放大數的長度（總共有幾位數？），預設為 0
*/

class BigInteger {
	private:
		int number[MAX_LENGTH];
		bool positive;
		int length;
	public:
		BigInteger();
		BigInteger(int);
		BigInteger(string);
		static int compare(BigInteger, BigInteger);
		BigInteger operator+(BigInteger);
		BigInteger operator-(BigInteger);
		BigInteger operator*(BigInteger);
		BigInteger operator/(BigInteger);
		friend ostream& operator<<(ostream&, BigInteger&); // operator<<() 不能宣告為 BigInteger 的 member function
};

BigInteger::BigInteger() {

/*
	思路：使用預設值初始化各個 data member
*/

// 提示：如何事後初始化陣列？不能用 number={0}，要用 memset()！
// memset 是定義在 <cstring> 裡的（C++ 的 <cstring> 就是 C 的 <string.h>）
	memset(number, 0, MAX_LENGTH);

}

BigInteger::BigInteger(string a) {

/*
	思路：假如已經得到一個用字串表示的大數，現在我們要將字串存進整數陣列 number[]
*/

/*
	作法：把每位數字倒過來存！
	e.g. "86452" 存進 number[] 陣列後應該是 number[] = {2, 5, 4, 6, 8, 0, ..., 0}
	這麼做是為了往後 a.number[0] 就是 a 的第一位（個位）數字，b.number[0] 也會是 b 的第一位數字……以此類推
*/

// 提示 1：從字串的最後一個字元開始往前讀取
// 注意並不是每個字元都是有效的數字，也可能是 '(', ')', '-'
	for (int i=a.length()-1; i>=0; --i)
		number[length++] = a[i] - '0';

// 提示 2：小心如果輸入的字串是 "0"，其長度 length 應該要是 0，不是 1
// 另外，如果輸入的字串是 "00086452" 呢？

}

BigInteger::BigInteger(int a) {

/*
	思路：假如已經得到一個整數，現在我們要將該整數存進整數陣列 number[]
*/

/*
	作法：將整數不斷 %10，/10 就可以得到該整數的每個位數，只不過要小心正負號
	另外還有一種比較懶的作法，就是先將整數轉換成字串，接下來就和上面的建構函式一模一樣囉！
*/

}

int BigInteger::compare(BigInteger a, BigInteger b) {

/*
	思路：若 a>b 傳回 1，a=b 傳回 0，a<b 傳回 -1
*/

/*
	作法：由共同的最高位數（i.e. number[length-1]）開始往下比
	只要 a.number[i]>b.number[i] 就可以確定 a>b，a.number[i]<b.number[i] 就可以確定 a<b
	如果剛好 a.number[i]=b.number[i] 才需要比下一位數字
*/

}

BigInteger BigInteger::operator+(BigInteger a) {

/*
	思路：模擬直式的加法運算，先考慮 被加數>0 且 加數>0 的情況
*/

/*
	作法：由最低位數開始往上兩兩相加，如果超過 10 就要進位！
	最後要修正相加後的和 c 的長度 c.length
	假如 a 有 m 位數，b 有 n 位數，那麼 a+b 會是幾位數呢？一定是 max(m, n) 嗎？或是 max(m, n)+1？
*/

// 提示 1：最重要的部份
	for (int i=0; i<len; ++i)
		c.number[i] += number[i] + a.number[i];

// 提示 2：上面講的是 a 跟 b 都是正數的情況，要求 a+b，萬一 a 或 b 是負數呢？
// 如果 a 是負的 => 要算 c = b - abs(a)；如果 b 是負的 => 要算 c = a - abs(b)
// 如果 a 和 b 都是負的 => 要算 c = abs(a) + abs(b)，再把 c 加負號
	if (positive && !a.positive)
		c = *this - a;

}

BigInteger BigInteger::operator-(BigInteger a) {

/*
	思路：模擬直式的減法運算，先考慮 被減數>0、減數>0 且 被減數-減數>0 的情況
*/

/*
	作法：由最低位數開始往上兩兩相減，如果小於 0 就要借位！
	最後要修正相減後的差 c 的長度 c.length
	假如 a 有 m 位數，b 有 n 位數，那麼 a-b 會是幾位數呢？一定是 m 位嗎？或者有可能少於 m 位嗎？
*/

// 提示 1：最重要的部份
	for (int i=0; i<len; ++i)
		c.number[i] += number[i] - a.number[i];

// 提示 2：跟前面的加法運算一樣，要另外考慮 a 或 b 是負數的情怳，還有 a>0、b>0 但 a-b 是負數的情況
	if (positive && a.positive)
		if (BigInteger::compare(*this, a) == -1)
			c = a - *this;

}

BigInteger BigInteger::operator*(BigInteger a) {

/*
	思路：模擬直式的乘法運算，先把被乘數和乘數都當作正數
	p.s. 別想用累加的，雖然根據定義 a*b 就是把 a 累加 b 次，但是這樣的效率極低
	     保證 TLE (time limit exceed)，連你都等不下去……不信你可以試試
*/

/*
	作法：兩數都從最低位數開始往上兩兩互乘，最後再一次解決超過 10 需進位的問題！
	最後要修正相乘後的積 c 的長度 c.length
	假如 a 有 m 位數，b 有 n 位數，那麼 a*b 會是幾位數呢？一定是 m+n 位嗎？或是 m+n+1？m+n-1？
*/

// 提示 1：最重要的部份
	for (int i=0; i<length; ++i)
		for (int j=0; j<a.length; ++j)
			c.number[i+j] += number[i] * a.number[j];

// 提示 2：c 的正負判斷很簡單，c = a*b，如果 a、b 同號 c 就是正的，否則 c 就是負的

// 提示 3：還有，如果 a 或 b 是 0 的話也要另外處理
// 還記得如何判斷一個大數 x 是不是為 0 嗎？
	if (x.length == 0) { ... }

}

BigInteger BigInteger::operator/(BigInteger a) {

/*
	思路：模擬直式的除法運算，先把被除數和除數都當作正數
*/

/*
	作法：呃…不好說…請參考提示 1 的虛擬碼（pseudo code），	你可以先回想一下小學是怎麼學除法的∼
	最後要修正相除後的商 c 的長度 c.length
	假如 a 有 m 位數，b 有 n 位數，那麼 a/b 會是幾位數呢？一定是 m-n+1 位嗎？或是 m-n？
*/

// 提示 1：除法的虛擬碼
// 看起來好像很簡單嘛……才怪！你自己寫寫看就知道有多煩了
	procedure division
		diff <- dividend.length-divisor.length
		while diff is no less than 0 do
			divisor <- divisor*10^diff
			for i from 0 to 10 do
				multiple <- divisor*i
				if multiple is larger than dividend then
					i <- i-1
					break for loop
				end if
			end for
			multiple <- divisor*i
			dividend <- dividend-multiple;
			i is the diff-th number of quotient
			diff <- diff-1;
		end while
	end procedure

// 提示 2：c 的正負判斷很簡單，c = a/b，如果 a、b 同號 c 就是正的，否則 c 就是負的

// 提示 3：除數不能為 0！！！萬一除數為 0 就直接傳回大數型別的 0
// 當然，更好的作法是 throw exception，不過你現在可能還不會

}

ostream& operator<<(ostream& os, BigInteger& a) {

/*
	思路：倒過來輸出大數的每個位數
*/

/*
	作法：由最高位數（i.e. a.number[a.length-1]）開始往下輸出
*/

// 提示：不要忘了 0 要輸出 "0"，還有負數要先輸出 "-"

}

int main() {

/*
	思路：讀取使用者指定的檔案，並執行檔案中的運算式，直到讀到檔案結尾
*/

/*
	作法：以讀取模示開啟指定的檔案，確認成功開啟後
	使用 while 迴圈讀取檔案內容，直到遇到 EOF (end-of-file) 指示符
	最後關閉檔案
*/

// 提示：你可以使用 C 的檔案 I/O 函式，不過使用 C++ 的檔案 I/O 或許會簡單一些
// 宣告 fstream 物件
	fstream input; // 請先引入 <fstream>
// 接著，以讀取模示開啟檔案
	input.open("path/to/your/file", ios::in); // C++ 的檔案開啟模式有 ios::in, ios::out, ios::binary,
	                                          // ios::ate, ios::app, ios::trunc，有興趣可以自己 google
// 判斷檔案是否開啟成功
	if (input.is_open()) { ... }
// 從檔案中讀入資料
	string str;
	input >> str;
// 判斷是否遇到 EOF（已讀到檔案結尾）
	if (input.eof()) { ... }
// 關閉檔案
	input.close();

}

/*
	進階解法 - 最佳化（optimize）大數運算的演算法
	i. number[] 的大小是 MAX_LENGTH，萬一長度超過 MAX_LENGTH 怎麼辦？
		可以用動態記憶體配置（dynamic memory allocation）
		也就是 int* number = new int[length]，但是，當然，不太好寫
	ii. 在整數陣列 number[] 裡，每個元素都可以存放一個 int 範圍的數字
	但是我們卻只會拿來存放 0 到 9，其他的空間就浪費掉了？
		所以我們可以設計成每個元素都拿來存放 0~99、0~999……
		不過在進位的時候就要小心溢位（overflow）的問題
	iii. 加法和減法有沒有更好的作法？
		可以將負數取補數，這麼一來，不管數字是正是負，要做加法還是減法
		都可以用同一套加法演算法來達成
	當然還有很多更好的最佳化技巧……有興趣可以自己 google
*/

/*
	範例測資與預期的輸出：

Please input the filename: test.txt
2222222222222222222222222 + 1111111111111111111111111 = 3333333333333333333333333
2222222222222222222222222 - 1111111111111111111111111 = 1111111111111111111111111
2222222222222222222222222 * -1111111111111111111111111 = -2469135802469135802469135308641975308641975308642
2222222222222222222222222 / -1111111111111111111111111 = -2
7562 + 99999 = 107561
7562 - 99999 = -92437
7562 * 99999 = 756192438
7562 / 99999 = 0
-7562 + 99999 = 92437
-7562 - 99999 = -107561
-7562 * 99999 = -756192438
-7562 / 99999 = 0
7562 + -99999 = -92437
7562 - -99999 = 107561
7562 * -99999 = -756192438
7562 / -99999 = 0
-7562 + -99999 = -107561
-7562 - -99999 = 92437
-7562 * -99999 = 756192438
-7562 / -99999 = 0
8756445 + 9735 = 8766180
8756445 - 9735 = 8746710
8756445 * 9735 = 85243992075
8756445 / 9735 = 899
0 + 0 = 0
0 - 0 = 0
0 * 0 = 0
0 / 0 = 0
3260 + 0 = 3260
0 + 3260 = 3260
3260 - 0 = 3260
0 - 3260 = -3260
3260 * 0 = 0
0 * 3260 = 0
3260 / 0 = 0
0 / 3260 = 0

*/

// 就寫到這裡，加油囉 ^__^
// b.t.w. 其實在很多程式語言裡，是有內建大數運算的函式庫的
// 例如 Java 有 BigInteger、BigDecimal class 可以用，所以往後你要寫大數運算其實可以不用那麼辛苦
