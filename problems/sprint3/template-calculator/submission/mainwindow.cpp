#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->l_result->setText("");
    ui->l_formula->setText("");
    ui->l_memory->setText("");
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::SetInputText(const std::string& text) {
    ui->l_result->setText(QString::fromStdString(text));
    ui->l_result->setStyleSheet("");
}

void MainWindow::SetErrorText(const std::string& text) {
    ui->l_result->setText(QString::fromStdString(text));
    ui->l_result->setStyleSheet("color: red;");
}

void MainWindow::SetFormulaText(const std::string& text) {
    ui->l_formula->setText(QString::fromStdString(text));
}

void MainWindow::SetMemText(const std::string& text) {
    ui->l_memory->setText(QString::fromStdString(text));
}

void MainWindow::SetExtraKey(const std::optional<std::string>& key) {
    if (key) {
        ui->tb_extra->setText(QString::fromStdString(key.value()));
        ui->tb_extra->setVisible(true);
    } else {
        ui->tb_extra->hide();
    }
}

void MainWindow::SetDigitKeyCallback(std::function<void(int key)> cb) {
    digit_key_callback_=cb;
}

void MainWindow::SetProcessOperationKeyCallback(std::function<void(Operation key)> cb) {
    operation_key_callback_=cb;
}

void MainWindow::SetProcessControlKeyCallback(std::function<void(ControlKey key)> cb) {
    control_key_callback_=cb;
}

void MainWindow::SetControllerCallback(std::function<void(ControllerType controller)> cb) {
    controller_callback_=cb;
}

void MainWindow::on_cmb_controller_currentIndexChanged(int index)
{
    if(!controller_callback_){
        return;
    }

    switch (index){
    case 0:
        controller_callback_(ControllerType::DOUBLE);
        break;
    case 1:
        controller_callback_(ControllerType::FLOAT);
        break;
    case 2:
        controller_callback_(ControllerType::UINT8_T);
        break;
    case 3:
        controller_callback_(ControllerType::INT);
        break;
    case 4:
        controller_callback_(ControllerType::INT64_T);
        break;
    case 5:
        controller_callback_(ControllerType::SIZE_T);
        break;
    case 6:
        controller_callback_(ControllerType::RATIONAL);
        break;
    default:
        break;
    }
}


void MainWindow::on_btn_mc_clicked()
{
    if(control_key_callback_){
        control_key_callback_(ControlKey::MEM_CLEAR);
    }
}


void MainWindow::on_btn_mr_clicked()
{
    if(control_key_callback_){
        control_key_callback_(ControlKey::MEM_LOAD);
    }
}


void MainWindow::on_btn_ms_clicked()
{
    if(control_key_callback_){
        control_key_callback_(ControlKey::MEM_SAVE);
    }
}


void MainWindow::on_btn_abs_clicked()
{
    if(operation_key_callback_){
        operation_key_callback_(Operation::POWER);
    }
}


void MainWindow::on_btn_c_clicked()
{
    if(control_key_callback_){
        control_key_callback_(ControlKey::CLEAR);
    }
}


void MainWindow::on_btn_plus_and_minus_clicked()
{
    if(control_key_callback_){
        control_key_callback_(ControlKey::PLUS_MINUS);
    }
}


void MainWindow::on_btn_dividing_clicked()
{
    if(operation_key_callback_){
        operation_key_callback_(Operation::DIVISION);
    }
}


void MainWindow::on_btn_mult_clicked()
{
    if(operation_key_callback_){
        operation_key_callback_(Operation::MULTIPLICATION);
    }
}


void MainWindow::on_btn_minus_clicked()
{
    if(operation_key_callback_){
        operation_key_callback_(Operation::SUBTRACTION);
    }
}


void MainWindow::on_btn_plus_clicked()
{
    if(operation_key_callback_){
        operation_key_callback_(Operation::ADDITION);
    }
}


void MainWindow::on_btn_equals_clicked()
{
    if(control_key_callback_){
        control_key_callback_(ControlKey::EQUALS);
    }
}


void MainWindow::on_btn_delete_clicked()
{
    if(control_key_callback_){
        control_key_callback_(ControlKey::BACKSPACE);
    }
}


void MainWindow::on_tb_extra_clicked()
{
    if(control_key_callback_){
        control_key_callback_(ControlKey::EXTRA_KEY);
    }
}


void MainWindow::on_btn_nine_clicked()
{
    if(digit_key_callback_){
        digit_key_callback_(9);
    }
}


void MainWindow::on_btn_eight_clicked()
{
    if(digit_key_callback_){
        digit_key_callback_(8);
    }
}


void MainWindow::on_btn_seven_clicked()
{
    if(digit_key_callback_){
        digit_key_callback_(7);
    }
}


void MainWindow::on_btn_six_clicked()
{
    if(digit_key_callback_){
        digit_key_callback_(6);
    }
}


void MainWindow::on_btn_five_clicked()
{
    if(digit_key_callback_){
        digit_key_callback_(5);
    }
}


void MainWindow::on_btn_four_clicked()
{
    if(digit_key_callback_){
        digit_key_callback_(4);
    }
}


void MainWindow::on_btn_three_clicked()
{
    if(digit_key_callback_){
        digit_key_callback_(3);
    }
}


void MainWindow::on_btn_two_clicked()
{
    if(digit_key_callback_){
        digit_key_callback_(2);
    }
}


void MainWindow::on_btn_one_clicked()
{
    if(digit_key_callback_){
        digit_key_callback_(1);
    }
}


void MainWindow::on_btn_zero_clicked()
{
    if(digit_key_callback_){
        digit_key_callback_(0);
    }
}
