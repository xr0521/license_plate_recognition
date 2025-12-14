#include "login.h"

Login::Login(QWidget *parent)
	: QDialog(parent)
{
	this->setWindowTitle(QString::fromLocal8Bit("登录界面"));
	this->setFixedSize(400, 550);
	Init();
    if (!Mysql_Init()) {
        std::cout << "MYSQL Init failed!!!" << std::endl;
        return;
    }
}

Login::~Login()
{}

void Login::Init()
{
    // 1. 创建控件
    login_label = new QLabel;
    img_map = new QPixmap("./resource/qq.png");
    login_label->setPixmap(*img_map);
    login_label->setStyleSheet("background: transparent;");
    login_btn = new QPushButton(QString::fromLocal8Bit("登录"));
    login_btn->setFixedSize(250, 40); // 按钮高度建议设死，防止变形
    connect(login_btn,&QPushButton::clicked,this,&Login::onclick_Login);

    line_user = new QLineEdit;
    line_user->setPlaceholderText(QString::fromLocal8Bit("请输入用户名/手机号"));
    line_user->setFixedSize(250, 40); // 这里建议用 FixedSize，比 MaximumSize 更稳定

    line_pwd = new QLineEdit;
    line_pwd->setPlaceholderText(QString::fromLocal8Bit("请输入密码"));
    line_pwd->setFixedSize(250, 40);
    line_pwd->setEchoMode(QLineEdit::Password);

    agree_btn = new QRadioButton(QString::fromLocal8Bit("我已同意并知晓"));
    // QRadioButton 默认高度可能只有 20px 左右，如果你想让它容易点中，可以设置稍微高一点
    agree_btn->setFixedHeight(30);

    // 2. 创建布局
    QVBoxLayout* centralLayout = new QVBoxLayout;

    // 【关键点1】添加顶部弹簧，把内容往下顶
    centralLayout->addStretch();
    centralLayout->addWidget(login_label, 0, Qt::AlignCenter);
    centralLayout->addWidget(line_user, 0, Qt::AlignHCenter);
    centralLayout->addWidget(line_pwd, 0, Qt::AlignHCenter);
    centralLayout->addWidget(agree_btn, 0, Qt::AlignHCenter);

    centralLayout->addWidget(login_btn, 0, Qt::AlignHCenter);

    // 【关键点2】添加底部弹簧，把内容往上顶
    centralLayout->addStretch();

    // 3. 设置间距
    // setMargin 已在 Qt5/6 中建议改用 setContentsMargins(左, 上, 右, 下)
    centralLayout->setContentsMargins(10, 10, 10, 10);

    // 这里设置 10 或 15 可能比 5 更好看，太挤了很难受
    centralLayout->setSpacing(20);

    this->setLayout(centralLayout);
    this->setObjectName("LoginWindow");
    this->setStyleSheet(
        "#LoginWindow {" // 2. 只针对这个名字的控件设置背景，不影响里面的按钮
        "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #89f7fe, stop:1 #66a6ff);"
        "}"
    );
    // 4. 【关键点3】设置样式，去除不必要的干扰
    // 这里的样式确保了控件之间没有额外的 margin 叠加
    this->setStyleSheet(R"(
    QLineEdit {
        border: 1px solid #ccc;
        border-radius: 4px;
        padding-left: 10px;
        /* 确保没有 margin 干扰 spacing */
        margin: 0px; 
    }
    QPushButton {
        background-color: #0078d7;
        color: white;
        border-radius: 4px;
        font-weight: bold;
        margin: 0px;
    }
    QRadioButton {
        /* 单选框文字和圆圈的间距 */
        spacing: 5px; 
        margin: 0px;
    }
)");
}

bool Login::Mysql_Init() {
    m_mysql = mysql_init(nullptr);
    if (m_mysql==nullptr) {
        return false;
    }
    m_mysql = mysql_real_connect(m_mysql,ip.c_str(),username.c_str(),pwd.c_str(),dbName.c_str(),port,nullptr,0);
    if (m_mysql == nullptr) {
        std::cout << "mysql_real_connect failed!!!" << std::endl;
        return false;
    }
    return true;
}

void Login::onclick_Login() {
    QString username = line_user->text().trimmed();
    QString pwd = line_pwd->text().trimmed();
    if (username.isEmpty() || pwd.isEmpty()) {
        QMessageBox::information(this, "Login", QString::fromLocal8Bit("用户/密码不能为NULL，请重新输入！"));
        return;
    }
    if (!agree_btn->isChecked()) {
        QMessageBox::information(this, "Login", QString::fromLocal8Bit("请点击用户须知！"));
        agree_btn->setFocus();

        // 2. 直接结束当前函数，不再执行后面的代码
        return;
    }
    std::string sql = "SELECT pwd FROM user WHERE name = '" + username.toStdString() + "'";
    // 2. 执行查询
// mysql_query 返回 0 表示成功，非 0 表示有错误
    int query_status = mysql_query(m_mysql, sql.c_str());

    if (query_status != 0) {
        // 查询失败
        std::cout << "Query failed: " << mysql_error(m_mysql) << std::endl;
        return;
    }
    else {
        // 3. 获取结果集 (这才是返回 MYSQL_RES* 的地方)
        MYSQL_RES* result = mysql_store_result(m_mysql);

        if (result) {
            // 获取行数
            my_ulonglong row_count = mysql_num_rows(result);
            if (row_count > 0) {
                // 获取第一行数据
                MYSQL_ROW row = mysql_fetch_row(result);
                if (row) {
                    std::string db_pwd = row[0]; // 第0列是 pwd
                    // 比对密码
                    if (db_pwd == pwd.toStdString()) {
                        QMessageBox::information(this, "Login", QString::fromLocal8Bit("登录成功！"));
                        this->hide();
                        this->accept();
                    }
                    else {
                        QMessageBox::information(this, "Login", QString::fromLocal8Bit("密码错误，请重新输入！"));
                        line_user->clear();
                        line_pwd->clear();
                    }
                }
            }
            else {
                QMessageBox::information(this, "Login", QString::fromLocal8Bit("用户名错误，请重新输入！"));
                line_user->clear();
                line_pwd->clear();
            }

            // 4. 重要：释放结果集内存
            mysql_free_result(result);
        }
    }
}