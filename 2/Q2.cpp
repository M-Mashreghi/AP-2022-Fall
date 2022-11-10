#include <iostream>
#include <string>
#include <cstdlib>

int START_letter = 0;

using namespace std;

void swap_2_letters(string& word, int from, int end) {
	char temp;

	temp = word[from];
	word[from] = word[end];
	word[end] = temp;

}


string swap_Coding(string& word, int& length_word, int from, int end)
{	

	if (length_word == 1) { return word; }//check length;

	swap_2_letters(word, from, end);//swap


	if ( (end - 1) <= (from + 2)) { return word; }//check end and from reach to each other

	else { return swap_Coding(word, length_word, from + 2, end - 1); }//caculate from and end for the next round


}


int main()
{
	string word ;
	cin >> word;
	int length_word = word.length();
	cout<<swap_Coding(word, length_word, START_letter , length_word - 1)<<endl;



}
