#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

#define FILE_COS_PATH "CustomerInfo.txt"
#define FILE_ADM_PATH "AdminInfo.txt"
#define FILE_RENT_PATH "RentalInfo.txt"
#define FILE_SITE_PATH "SiteInfo.txt"

#define ID_LEN 30
#define NAME_LEN 20
#define PHONE_NUM_LEN 12
#define KEY_LEN 20
#define MAIL_ADDRESS_LEN 20
#define TIME_LEN 20
#define INTRO_LEN 300

#define RENT_INFO_LEN 20
#define SITE_INFO_LEN 20
#define CUS_INFO_LEN 20

#define CUS_LEN 40
#define ADM_LEN 40
#define RENT_LEN 40
#define SITE_LEN 40

#define VENUE_NAME_LEN 20
#define SEX_LEN 10
#define REGION_LEN 20
#define SPORT_LEN 10

extern int cus_size;
extern int adm_size;
extern int rent_size;
extern int site_size;

//int cus_rent_size = 0;
//int adm_site_size = 0;
//int site_rent_size = 0;

typedef struct CustomerInfo{
    struct RentalInfo * (*rent_info);
    char ID[ID_LEN];
    char name[NAME_LEN];
    char phone_num[PHONE_NUM_LEN];
    char key[KEY_LEN];
    char e_mail[MAIL_ADDRESS_LEN];
//    enum sex_type sex;
//    enum region_type region;
    char sex[SEX_LEN];
    char region[REGION_LEN];
    double balance;
    int age;
    int default_num;/* 爽约次数 */
    int rent_info_len;
}CustomerInfo;

typedef struct AdminInfo{
    struct SiteInfo * (*site_info);
    char ID[ID_LEN];
    char name[NAME_LEN];
//    enum vanue vanue_name;
    char venue_name[VENUE_NAME_LEN];
    char key[KEY_LEN];
    char e_mail[MAIL_ADDRESS_LEN];
//    enum sex_type sex;
    char sex[SEX_LEN];
    char phone_num[PHONE_NUM_LEN];
    int site_info_len;
}AdminInfo;

typedef struct RentalInfo{
    struct CustomerInfo * cus_info;
    struct SiteInfo * site_info;
//    char site_ID[ID_LEN];
    char Appoint_ID[ID_LEN];
//    char start_time[TIME_LEN];
//    char end_time[TIME_LEN];
//    char Appoint_time[TIME_LEN];
    int start_time[2];
    int end_time[2];
    int appoint_time[5];
    int start_date[3];
    double price;/* 保留两位小数 */
    int is_intime;/* true or false *//* 修改类型 */
//    eunum sex_type sex;
    char gender[SEX_LEN];
    int age;
    int is_complete;/* 判断是否完成，0(未完成)，1（完成），-1（取消）,这个是新加的 */
}RentalInfo;


typedef struct SiteInfo{
    struct RentalInfo * (*rent_info);
    struct AdminInfo * admin_info;
    char ID[ID_LEN];
//    enum vanue vanue_name;/* （综合）场馆 */
//    char venue_name[VENUE_NAME_LEN];
//    enum region_type region;
    char region[REGION_LEN];
//    enum sport_type sport;
    char sport[SPORT_LEN];
    char intro[INTRO_LEN];/*????????*/
    int enter_age;/* 准入年龄 */
    double rent;/* 租金 */
    double total_profit;/* 总营业额 */
    int order_num;/* 预定量 */
    int rent_info_len;
}SiteInfo;

extern CustomerInfo ** customer;
extern AdminInfo ** admin;
extern SiteInfo ** site;
extern RentalInfo ** rent;
static int start_time[5]={2018,9,10,0,0};

void _arr_init();/* read msg from file, and create an array which has the msg */

/* search relevant function  */
CustomerInfo * search_cus_ID(char * ID);
AdminInfo * search_adm_ID(char * ID);
RentalInfo * search_rent_ID(char * ID);
SiteInfo * search_site_ID(char * ID);

/* compare dependence */
int _comp_cus_age_down(const void *,const void *);
int _comp_cus_age_up(const void *a,const void *b);
int _comp_site_rent_down(const void *a,const void *b);
int _comp_site_rent_up(const void *a,const void *b);
int _comp_site_order_down(const void *a,const void *b);
int _comp_site_order_up(const void *a,const void *b);
int _comp_site_profit_down(const void *a,const void *b);
int _comp_site_profit_up(const void *a,const void *b);
int _comp_site_untilize_down(const void *a,const void *b);/* 未 */
int _comp_site_untilize_up(const void *a,const void *b);/* 未 */
int _comp_female_sport(const void *a,const void *b);/* 未 */
int _comp_male_sport(const void *a,const void *b);/* 未 */

/* menu */
void main_menu(void);
void user_func_menu(void);
void adm_func_menu(void);
void reserve_management_menu(void);
void count_order_menu(void);
void site_management_menu();
void cos_modify_menu();
void adm_modify_menu();
void register_menu();
void search_menu(void);
void category_menu(void);
void book_venue_menu();
void book_sport_menu();
void _private_book_region_menu();
void sort_menu(void);

/* be friendly to user */
int _get_int (void);
int _check_phone(char * phone_num);/* 未检测 */
int _check_password(char * password);/* 未检测 */
int _check_ID(char * ID);/* 未检测 */
int _check_mail(char * mail);/* 未检测 */
int _check_24_hour(int* starttime);/* 未检测 */

/* choice relevant */
CustomerInfo * Login_user();/* 未检测 */
AdminInfo * Login_adm();/* 未检测 */
int revise_customer_info(CustomerInfo * cos);/* 未检测 */
int revise_admin_info(AdminInfo * adm);/* 未检测 */
void cus_show_orders(CustomerInfo * cos);/* 未检测 */
void adm_show_orders(AdminInfo * adm);/* 未检测 */
void adm_show_site(AdminInfo * adm);/* 未 */


/* statistics */
float _get_utilize_rate(SiteInfo * siteInfo);/* 未检测 */
void get_cur_time(int * cur_time);/* 已检测 */
double get_venue_profit(AdminInfo * adminInfo);/* 未检测 */
int get_female_sport_num(SiteInfo * siteInfo);/* 未检测 */
int get_male_sport_num(SiteInfo * siteInfo);/* 未检测 */
void analyse_age(AdminInfo * adminInfo);/* 未 */
int _get_time_len(int * starttime,int * endtime);/* 未 */

/* not do */
int add_site();
int add_rent();
int add_cus();
int add_admin();
void inter_search();
int cancel_order();/* 未检测，没调用 */
void free_all();

/* 扩容函数 */
void _increase_adm_room();
void _increase_cus_room();
void _increase_site_room();
void _increase_rent_room();
void _increase_adm_site_room(AdminInfo * adm);
void _increase_site_rent_room(SiteInfo * siteInfo);
void _increase_cus_rent_room(CustomerInfo * cus);