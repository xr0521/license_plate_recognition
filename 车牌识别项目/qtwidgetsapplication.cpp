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
    layout->addLayout(leftLayout, 2);
    layout->addLayout(rightLayout, 4);
    layout->setSpacing(0);
    // 去掉边距，填满整个窗口
    layout->setContentsMargins(0, 0, 0, 0);
    backLabel = new QLabel;
    backImg = new QPixmap("./resource/chexing.jpg");
    int newWidth = 200;
    int newHeight = 150;
    QPixmap scaledImg = backImg->scaled(newWidth, newHeight,
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation);

    backLabel->setPixmap(scaledImg);
    backLabel->setMargin(40);
    // 1. 创建网格布局
    QGridLayout* layout = new QGridLayout();
    layout->setSpacing(10); // 设置行距和列距
    layout->setContentsMargins(20, 20, 20, 20); // 设置四周留白

    // 定义数据（模拟图中的内容）
    struct Item {
        QString iconPath;
        QString text;
    };

    // 这里假设你已经有了对应的图标文件
    QList<Item> items = {
        {"./resource/File.png", QString::fromLocal8Bit("请选择文件夹")},
        {"./resource/Location.png",  QString::fromLocal8Bit("实时视频已关闭")},
        {"./resource/open.png",  QString::fromLocal8Bit("图片文件未选中")},
        {"./resource/video.png", QString::fromLocal8Bit("相机准备就绪")}
    };

    // 2. 循环创建每一行
    for (int i = 0; i < items.size(); ++i) {
        // --- 左侧图标 ---
        QPushButton* iconLabel = new QPushButton(QIcon(items[i].iconPath),"Button");
        iconLabel->setStyleSheet("border: none; background-color: transparent; color: #3399FF; text-align: left;");
        iconLabel->setStyleSheet(R"(
    QPushButton {
        border: none;              /* 去除边框 */
        background: transparent;   /* 背景透明 */
        text-align: left;          /* 文字靠左 */
        padding-left: 10px;        /* 文字和图标稍微往右移一点，不贴边 */
    }
    QPushButton:hover {
        background-color: #E6F3FF; /* 鼠标悬停时变成淡蓝色，提示用户可点击 */
    }
    QPushButton:pressed {
        background-color: #D0E8FF; /* 鼠标按下时颜色更深一点 */
    }
)");
        // --- 右侧文本框 ---
        QLineEdit* textField = new QLineEdit;
        textField->setText(items[i].text);
        textField->setReadOnly(true); // 设为只读，鼠标点进去不能修改，但可以复制
        // 如果完全不想让鼠标交互，可以 textField->setEnabled(false); 但颜色会变灰，需要额外设置样式
        textField->setFocusPolicy(Qt::NoFocus); // 也可以设置不获取焦点

        // --- 添加到布局 (行, 列) ---
        layout->addWidget(iconLabel, i, 0); // 第 i 行，第 0 列
        layout->addWidget(textField, i, 1); // 第 i 行，第 1 列
        switch (i)
        {
        case 0:
            fileBtn = iconLabel;
            fileEdit = textField;
            break;
        case 1:
            videoBtn = iconLabel;
            videoEdit = textField;
            break;
        case 2:
            imgBtn = iconLabel;
            imgEdit = textField;
            break;
        case 3:
            cameraBtn = iconLabel;
            cameraEdit = textField;
            break;
        default:
            break;
        }
    }
    QPixmap map("./resource/rocket.png");
    QPixmap newMap = map.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    runBtn = new QPushButton(QIcon(newMap), QString::fromLocal8Bit("开始运行"));
    leftLayout->addWidget(backLabel,0, Qt::AlignCenter);
    leftLayout->addLayout(layout);
    leftLayout->addWidget(runBtn, 0, Qt::AlignCenter);
    leftLayout->setContentsMargins(0, 0, 0, 0);
    leftLayout->addStretch();
    titleLabel = new QLabel(QString::fromLocal8Bit("中文车牌识别系统"));
    // 1. 创建字体对象
    QFont font;
    font.setFamily("Microsoft YaHei"); // 设置字体：微软雅黑
    font.setPointSize(20);             // 设置字号：20点
    font.setBold(true);                // 设置加粗

    // 2. 将字体应用到 Label
    titleLabel->setFont(font);
    imgLabel = new QLabel("Label");
    QPixmap carMap("./resource/car.jpg");
    imgLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    const int w = imgLabel->width();
    const int h = imgLabel->height();
    QPixmap carMap1 = carMap.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    imgLabel->setPixmap(carMap1);
    imgLabel->setScaledContents(true);
    rightTopLayout->setContentsMargins(0, 0, 0, 0);
    rightTopLayout->setSpacing(0); // 如果布局里只有这一个控件，设不设 spacing 无所谓
    rightTopLayout->addWidget(titleLabel,0,Qt::AlignCenter);
    rightTopLayout->addWidget(imgLabel);
    QString style = R"(
        /* 文本框样式：灰边框、淡蓝字、白背景 */
        QLineEdit {
            border: 1px solid #A0A0A0;
            color: #3399FF;
            background-color: white;
            font-size: 14px;
            padding-left: 5px;
            border-radius: 0px; /* 直角边框 */
        }
        
        /* 如果你想让整体背景变淡蓝，可以设置 parent 的背景 */
         QWidget { background-color: #F0F5FF; } 
    )";
    this->setStyleSheet(style);
    // 1. 创建表格对象
    QTableWidget* tableWidget = new QTableWidget;

    // 2. 设置列数和表头内容
    QStringList headerText;
    headerText << QString::fromLocal8Bit("序号") << QString::fromLocal8Bit("画面标识")\
        << QString::fromLocal8Bit("车牌") << QString::fromLocal8Bit("位置") << QString::fromLocal8Bit("置信度");
    tableWidget->setColumnCount(headerText.count());
    tableWidget->setHorizontalHeaderLabels(headerText);

    // 3. 配置表格行为（美观关键点）
    // 隐藏最左边的垂直行号
    tableWidget->verticalHeader()->setVisible(false);
    // 开启斑马线背景色（隔行变色）
    tableWidget->setAlternatingRowColors(true);
    // 设置整行选中，而不是选中单个单元格
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    // 禁止编辑单元格（如果你只是展示结果）
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // 去除选中时的虚线框
    tableWidget->setFocusPolicy(Qt::NoFocus);

    // 4. 设置列宽策略
    // 让所有列自动平均撑满宽度
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // 【优化】：由于"序号"列不需要太宽，可以单独把它设为固定宽度，其他的自动拉伸
    // tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    // tableWidget->setColumnWidth(0, 60);

    // 5. 设置样式表 (QSS) - 还原你截图的白色扁平风格
    QString tableStyle = R"(
    QTableWidget {
        background-color: #FFFFFF;
        border: 1px solid #E0E0E0;    /* 整体灰色细边框 */
        gridline-color: #F0F0F0;      /* 内部网格线颜色 */
        font-family: "Microsoft YaHei"; /* 微软雅黑 */
        font-size: 14px;
    }
    QHeaderView::section {
        background-color: #FFFFFF;    /* 表头白色背景 */
        color: #333333;               /* 表头字体深灰 */
        border: none;
        border-right: 1px solid #E0E0E0; /* 表头右分割线 */
        border-bottom: 1px solid #E0E0E0;/* 表头下分割线 */
        height: 35px;                 /* 表头高度 */
        font-weight: bold;            /* 表头加粗 */
    }
    QTableWidget::item {
        padding-left: 5px;            /* 内容左边距 */
    }
    /* 选中行的颜色（淡蓝色） */
    QTableWidget::item:selected {
        background-color: #E6F3FF;
        color: black;
    }
)";
    tableWidget->setStyleSheet(tableStyle);
    // 6. 【关键一步】将表格加入到 bottomLayout 中
    bottomLayout->addWidget(tableWidget);
    /*
    点击事件
    */
    connect(fileBtn, &QPushButton::clicked, [=]() {
        std::cout << "fileBtn is clicked" << std::endl;
        QString  fileName = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("选择文件"), "./",
            "图片文件 (*.jpg *.png *.bmp);;视频文件 (*.mp4 *.avi);;所有文件 (*.*)");
        if (fileName.isEmpty()) {
            qDebug() << "User cancelled";
            return;
        }
        fileEdit->setText(fileName);
        qDebug() << "fileName:" << fileName;
        QPixmap map(fileName);
        const int w = imgLabel->width();
        const int h = imgLabel->height();
        imgMap = map.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        imgLabel->setPixmap(imgMap);
        });
}
   
