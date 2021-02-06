/*
We keep track of the revenue Facebook makes every day, and we want to know on what days Facebook hits certain revenue milestones. Given an array of the revenue on each day, and an array of milestones Facebook wants to reach, return an array containing the days on which Facebook reached every milestone.
Signature
int[] getMilestoneDays(int[] revenues, int[] milestones)
Input
revenues is a length-N array representing how much revenue FB made on each day (from day 1 to day N). milestones is a length-K array of interesting total revenue milestones.
Output
Return a length-K array where K_i is the day on which FB first had milestones[i] total revenue.
Example
revenues = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
milestones = [100, 200, 500]
output = [4, 6, 10]
Explanation
On days 4, 5, and 6, FB has total revenue of $100, $150, and $210 respectively. Day 6 is the first time that FB has >= $200 of total revenue.
*/

vector < int > getMilestoneDays(const vector < int > &revenues, const vector < int > &milestones)
{
 int rev_len=int(revenues.size());
 int ms_len=int(milestones.size());
 vector < int > res(ms_len);
 vector < int > sums(1+rev_len);
 for(int i=0;i<rev_len;i++) sums[i+1]=sums[i]+revenues[i];
 for(int i=0;i<ms_len;i++) res[i]=lower_bound(sums.begin(),sums.end(),milestones[i])-sums.begin();
 return res;
}
