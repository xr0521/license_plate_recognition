#include "qtwidgetsapplication.h"

QtWidgetsApplication::QtWidgetsApplication(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    this->setFixedSize(830,600);
    Init();
}

QtWidgetsApplication::~QtWidgetsApplication()
{}

void QtWidgetsApplication::Init()
{
    // 1. 创建一个用于容纳所有内容的 Widget
    QWidget* centerWidget = new QWidget(this);

    // 2. 将其设置为 QMainWindow 的中心部件
    this->setCentralWidget(centerWidget);

    // 3. 将总布局的父对象设置为这个 centerWidget，而不是 this
    layout = new QHBoxLayout(centerWidget);

    // =========================================================
    //  以下是你的原有逻辑 (保持不变)
    // =========================================================

    leftLayout = new QVBoxLayout();
    rightLayout = new QVBoxLayout();
    rightTopLayout = new QVBoxLayout();
    bottomLayout = new QVBoxLayout();

    // --- 可视化测试控件 ---

    // 左侧（红色）
    QWidget* leftDummy = new QWidget;
    leftDummy->setStyleSheet("background-color: #FFCCCC; border: 2px solid red;");
    leftLayout->addWidget(leftDummy);

    // 右上（绿色）
    QWidget* topDummy = new QWidget;
    topDummy->setStyleSheet("background-color: #CCFFCC; border: 2px solid green;");
    rightTopLayout->addWidget(topDummy);

    // 底部（蓝色）
    QWidget* bottomDummy = new QWidget;
    bottomDummy->setStyleSheet("background-color: #CCCCFF; border: 2px solid blue;");
    bottomLayout->addWidget(bottomDummy);

    // --- 组装布局 ---

    // 右侧内部组装 (右上 : 右下 = 3 : 1)
    rightLayout->addLayout(rightTopLayout, 3);
    rightLayout->addLayout(bottomLayout, 1);

    // 整体组装 (左 : 右 = 1 : 4)
    layout->addLayout(leftLayout, 1);
    layout->addLayout(rightLayout, 4);

    // 去掉边距，填满整个窗口
    layout->setContentsMargins(0, 0, 0, 0);
}
