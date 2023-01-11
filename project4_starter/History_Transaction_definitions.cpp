#include <cassert>
#include <iomanip>
#include <iostream>

#include "project4.hpp"
#include "History.hpp"
#include "Transaction.hpp"

////////////////////////////////////////////////////////////////////////////////
// Definitions for Transaction class
////////////////////////////////////////////////////////////////////////////////
//
//

// Constructor
// TASK 1
//
Transaction::Transaction(std::string ticker_symbol, unsigned int day_date,
                         unsigned int month_date, unsigned int year_date,
                         bool buy_sell_trans, unsigned int number_shares,
                         double trans_amount) {
    symbol = ticker_symbol;
    day = day_date;
    month = month_date;
    year = year_date;
    p_next = nullptr;
    if (buy_sell_trans)
        trans_type = "Buy";
    else
        trans_type = "Sell";
    shares = number_shares;
    amount = trans_amount;
    trans_id = assigned_trans_id;
    ++assigned_trans_id;
    acb = 0;
    acb_per_share = 0;
    share_balance = 0;
    cgl = 0;
}

// Destructor
// TASK 1
//
Transaction::~Transaction() {
}

// Overloaded < operator.
// TASK 2
//
bool Transaction::operator<(Transaction const &other) {
    if (this->year < other.year) {
        return true;
    } else if (this->year == other.year && this->month < other.month) {
        return true;
    } else if (this->year == other.year && this->month == other.month && this->day < other.day) {
        return true;
    } else if (this->year == other.year && this->month == other.month && this->day == other.day &&
               this->trans_id > other.trans_id) {
        return true;
    }
    return false;
}

// GIVEN
// Member functions to get values.
//
std::string Transaction::get_symbol() const { return symbol; }

unsigned int Transaction::get_day() const { return day; }

unsigned int Transaction::get_month() const { return month; }

unsigned int Transaction::get_year() const { return year; }

unsigned int Transaction::get_shares() const { return shares; }

double Transaction::get_amount() const { return amount; }

double Transaction::get_acb() const { return acb; }

double Transaction::get_acb_per_share() const { return acb_per_share; }

unsigned int Transaction::get_share_balance() const { return share_balance; }

double Transaction::get_cgl() const { return cgl; }

bool Transaction::get_trans_type() const { return (trans_type == "Buy") ? true : false; }

unsigned int Transaction::get_trans_id() const { return trans_id; }

Transaction *Transaction::get_next() { return p_next; }

// GIVEN
// Member functions to set values.
//
void Transaction::set_acb(double acb_value) { acb = acb_value; }

void Transaction::set_acb_per_share(double acb_share_value) { acb_per_share = acb_share_value; }

void Transaction::set_share_balance(unsigned int bal) { share_balance = bal; }

void Transaction::set_cgl(double value) { cgl = value; }

void Transaction::set_next(Transaction *p_new_next) { p_next = p_new_next; }

// GIVEN
// Print the transaction.
//
void Transaction::print() {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << std::setw(4) << get_trans_id() << " "
              << std::setw(4) << get_symbol() << " "
              << std::setw(4) << get_day() << " "
              << std::setw(4) << get_month() << " "
              << std::setw(4) << get_year() << " ";

    if (get_trans_type()) {
        std::cout << "  Buy  ";
    } else {
        std::cout << "  Sell ";
    }

    std::cout << std::setw(4) << get_shares() << " "
              << std::setw(10) << get_amount() << " "
              << std::setw(10) << get_acb() << " " << std::setw(4) << get_share_balance() << " "
              << std::setw(10) << std::setprecision(3) << get_acb_per_share() << " "
              << std::setw(10) << std::setprecision(3) << get_cgl()
              << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
// Definitions for the History class
////////////////////////////////////////////////////////////////////////////////
//
//

// Constructor
// TASK 3
//
History::History() {
    p_head = nullptr;
}

// Destructor
// TASK 3
//
History::~History() {

    // Transaction *current = p_head;
    // while (current != nullptr)
    // {
    //   Transaction *next = current->get_next();
    //   delete current;
    //   // current = nullptr;
    //   current = next;
    // }
    // delete p_head;
    // p_head = nullptr;
    Transaction *current = p_head;
    while (current != nullptr) {
        Transaction *next = current;
        current = current->get_next();
        delete next;
//         current = nullptr;
//         current = next;
    }

    // p_head = nullptr;
}

// read_history(...): Read the transaction history from file.
// TASK 4
//
void History::read_history() {
    ece150::open_file();
    while (ece150::next_trans_entry()) {
        insert(new Transaction(ece150::get_trans_symbol(),
                               ece150::get_trans_day(),
                               ece150::get_trans_month(),
                               ece150::get_trans_year(),
                               ece150::get_trans_type(),
                               ece150::get_trans_shares(),
                               ece150::get_trans_amount()));
    }
//    ece150::close_file();
//     insert(new Transaction("ABC",
//                            12,
//                            04,
//                            2018,
//                            true,
//                            1000,
//                            12138.00));
//
//     insert(new Transaction("ABC",
//                            28,
//                            11,
//                            2019,
//                            true,
//                            27839,
//                            12138382.00));
//    insert(new Transaction("ABC",
//                           12,
//                           04,
//                           2018,
//                           true,
//                           1000,
//                           12138.00));
//
//    insert(new Transaction("ABC",
//                           28,
//                           11,
//                           2019,
//                           false,
//                           27839,
//                           12138382.00));
//    insert(new Transaction("ABC",
//                           12,
//                           04,
//                           2018,
//                           false,
//                           1000,
//                           12138.00));
//
//    insert(new Transaction("ABC",
//                           28,
//                           11,
//                           2019,
//                           true,
//                           27839,
//                           12138382.00));
//    insert(new Transaction("ABC",
//                           12,
//                           04,
//                           2018,
//                           true,
//                           1000,
//                           12138.00));
//
//    insert(new Transaction("ABC",
//                           28,
//                           11,
//                           2019,
//                           true,
//                           27839,
//                           12138382.00));
//    insert(new Transaction("ABC",
//                           12,
//                           04,
//                           2018,
//                           true,
//                           1000,
//                           12138.00));
//
//    insert(new Transaction("ABC",
//                           28,
//                           11,
//                           2019,
//                           false,
//                           27839,
//                           12138382.00));
//    insert(new Transaction("ABC",
//                           12,
//                           04,
//                           2018,
//                           false,
//                           1000,
//                           12138.00));
//
//    insert(new Transaction("ABC",
//                           28,
//                           11,
//                           2019,
//                           true,
//                           27839,
//                           12138382.00));
}

// insert(...): Insert transaction into linked list.
// TASK 5
//
void History::insert(Transaction *p_new_trans) {

    if (p_head == nullptr) {
        p_head = p_new_trans;
    } else {
        Transaction *p_temp = p_head;
        while (p_temp->get_next() != nullptr) {
            p_temp = p_temp->get_next();
        }
        p_temp->set_next(p_new_trans);
    }
}

// sort_by_date(): Sort the linked list by trade date.
// TASK 6
//
void History::sort_by_date() {
    Transaction *temp1 = nullptr;
    Transaction *dummy = new Transaction("ticker_symbol", 0, 0, 0,
                                         0, 0,
                                         0);
    Transaction *prev = nullptr;
    Transaction *next = nullptr;
    while (p_head != nullptr) {
        Transaction *min = p_head;
        dummy->set_next(p_head);
        Transaction *temp2 = dummy;
        while (temp2->get_next() != nullptr) {
            if (*temp2->get_next() < *min) {
                min = temp2->get_next();
                prev = temp2;
                next = temp2->get_next()->get_next();
            }
            temp2 = temp2->get_next();
        }
        if (min == p_head) {
            p_head = p_head->get_next();
            dummy->set_next(p_head);
//p_head->set_next(p_head->get_next());
        } else {
            prev->set_next(next);
        }
        min->set_next(nullptr);

        if (temp1 == nullptr) { //新list
            temp1 = min;
        } else {
            Transaction *p_temp = temp1;
            while (p_temp->get_next() != nullptr) {
                p_temp = p_temp->get_next();
            }
            p_temp->set_next(min);
        }
    }
    p_head = temp1;
    delete dummy;
//    delete temp1;
//    delete prev;
//    delete next;
}
//    Transaction *temp2 = nullptr;
//
//
//    while (p_head != nullptr) {
//        Transaction *temp1 = p_head;
//        Transaction *min = p_head;
//        while (temp1->get_next()!= nullptr) {
//            if (*temp1->get_next() < *min) {//找min
//                min = temp1->get_next();
//            }
//            temp1 = temp1->get_next();
//        }
//        if(min == p_head){
//            p_head = p_head->get_next();
//        }
//
//        Transaction *temp3 = p_head;
//        while (temp3->get_next()!= nullptr) {
//            if (temp3->get_next() == min) {
//                temp3->set_next(temp3->get_next()->get_next());
//                min->set_next(nullptr);
//                break;
//            }
//            temp3 = temp3->get_next();
//        }
//
//        if (temp2 == nullptr) { //新list
//            temp2 = min;
//        } else {
//            Transaction *p_temp = temp2;
//            while (p_temp->get_next() != nullptr) {
//                p_temp = p_temp->get_next();
//            }
//            p_temp->set_next(min);
//        }



//        Transaction *temp3 = nullptr;
//        if (min != p_head) {
//            Transaction *temp4 = p_head;
//            while (temp4->get_next() != nullptr) {
//                if (temp4->get_next()==min){
//                    temp3 = temp4;
//                }
//                temp4=temp4->get_next();
//            }
//            temp3->set_next(min->get_next());
//           min = nullptr;
//            //delete temp3;
//        } else {
//            p_head = p_head->get_next();
//        }
//    }
//    p_head = temp2;
//        while(temp1->get_next() == min) {//删min
//                    now=temp1->get_next();
//                   delete temp1->get_next();
//                   temp1->set_next(now->get_next());
//            Transaction *temp3 = temp1->get_next();
//            temp1->set_next(temp1->get_next()->get_next());
//            delete temp3;
//        } else if (p_head == min) {
//            Transaction *temp3 = p_head;
//            p_head = p_head->get_next();
//            delete temp3;
//        }
//        delete temp1;
//        delete min;



//temp2 = nullptr;

//    Transaction *temp = nullptr;
//    bool isChange = true;
//    while (temp != p_head->get_next() && isChange) {
//        Transaction *p_temp = p_head;
//        isChange = false;
//        for (; p_temp->get_next() && p_temp->get_next() != temp; p_temp = p_temp->get_next()) {
//            if (p_temp->get_next() < p_temp) {
//
//                Transaction *temp1 = nullptr;
//                temp1 = p_head->get_next();
//                *temp1 = *p_temp;
//                p_head = p_head->get_next();
//                p_head->set_next(temp1);
//                *temp1 = *p_head->get_next();
//                *p_head = *temp1;
//                *temp1->get_next() = *p_head;
//                isChange = true;
//                delete temp1;
//            }
//
//        }
//        temp = p_temp;
//    }



// update_acb_cgl(): Updates the ACB and CGL values.
// TASK 7
//
void History::update_acb_cgl() {
    Transaction *temp = p_head;
//    while (temp != nullptr) {
//        if (temp->get_trans_type()) {
//            temp->set_acb(temp->get_acb() + temp->get_amount());
//            temp->set_share_balance(temp->get_share_balance() + temp->get_shares());
//            temp->set_acb_per_share(temp->get_acb() / temp->get_share_balance());
//        } else {
//            temp->set_acb(temp->get_acb() - (temp->get_shares() * temp->get_acb_per_share()));
//            temp->set_share_balance(temp->get_share_balance() - temp->get_shares());
//            temp->set_cgl(temp->get_amount() - (temp->get_shares() * temp->get_acb_per_share()));
//        }
//        if (temp->get_next() != nullptr) {
//            temp->get_next()->set_acb(temp->get_acb());
//            temp->get_next()->set_share_balance(temp->get_share_balance());
//            temp->get_next()->set_acb_per_share(temp->get_acb_per_share());
//        }
//        temp = temp->get_next();
//    }

    double tempAcb = 0;
    double tempSbalance = 0;
    double tempApshare = 0;

    while (temp != nullptr) {
        if (temp->get_trans_type()) {
            temp->set_acb(tempAcb + temp->get_amount());
            tempAcb = temp->get_acb();
            temp->set_share_balance(tempSbalance + temp->get_shares());
            tempSbalance = temp->get_share_balance();
            temp->set_acb_per_share(tempAcb / tempSbalance);
            tempApshare = temp->get_acb_per_share();
        } else {
            temp->set_acb(tempAcb - (temp->get_shares() * tempApshare));
            tempAcb = temp->get_acb();
            temp->set_share_balance(tempSbalance - temp->get_shares());
            tempSbalance = temp->get_share_balance();
            temp->set_cgl(temp->get_amount() - (temp->get_shares() * tempApshare));
        }

        temp = temp->get_next();
    }

}

// compute_cgl(): )Compute the ACB, and CGL.
// TASK 8
double History::compute_cgl(unsigned int year) {
    double total = 0;
    Transaction *temp = p_head;
    while (temp != nullptr) {
        if (temp->get_year() == year) {
            total = total + temp->get_cgl();
        }
        temp = temp->get_next();
    }
    delete temp;
    return total;
}

// print() Print the transaction history.
// TASK 9
//
void History::print() {
    std::cout << "========== BEGIN TRANSACTION HISTORY ===========" << std::endl;
    Transaction *temp = p_head;
    while (temp != nullptr) {
        temp->print();
        temp = temp->get_next();
    }
    std::cout << "========== END TRANSACTION HISTORY ===========" << std::endl;
}

// GIVEN
// get_p_head(): Full access to the linked list.
//
Transaction *History::get_p_head() {
    return p_head;
}
