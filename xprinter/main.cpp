#include <QCoreApplication>
#include <QPrinter>
#include <QPdfDocument>
#include <QPainter>
#include <QPageSize>
#include <QApplication>
#include <QPdfDocumentRenderOptions>
#include <QPrinterInfo>
#include <iostream>


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);


    if(argc < 2) {
        std::cerr << "Please provide the path to PDF as argument";
        return -1;
    }

    QString pdfPath = argv[1];
    std::cout << "Loading PDF from: " << pdfPath.toStdString() << std::endl;

    QList<QPrinterInfo> availablePrinters  = QPrinterInfo::availablePrinters();

    if(availablePrinters.isEmpty()) {
        std::cerr << "No available printers." << std::endl;
        return -1;
    }

    std::cout << "Choose a printer: \n";
    for (int i = 0; i < availablePrinters.size(); ++i) {
        std::cout << i+1 << ". " << availablePrinters.at(i).printerName().toStdString() << "\n";
    }

    int printerIndex = -1;
    std::cout << "Enter printer number: ";
    std::cin >> printerIndex;

    if(printerIndex < 1 || printerIndex > availablePrinters.size()) {
        std::cerr << "Invalid printer index." << std::endl;
        return -1;
    }

    QPrinter printer(availablePrinters.at(printerIndex-1), QPrinter::HighResolution);
    printer.setFullPage(true);

    int mmWidth, mmHeight;
    std::cout << "Enter paper params (millimeters)\n";
    std::cout << "Width: ";
    std::cin >> mmWidth;
    std::cout << "Height: ";
    std::cin >> mmHeight;

    QPageSize pageSize(QSizeF(mmWidth, mmHeight), QPageSize::Millimeter);
    printer.setPageSize(pageSize);

    QSize pageSizePixels(printer.pageRect(QPrinter::DevicePixel).width(), printer.pageRect(QPrinter::DevicePixel).height());

    QPdfDocument pdfDoc;
    if(QPdfDocument::Error::None != pdfDoc.load(pdfPath)) {
        qDebug() << "Error loading pdf";
        return -1;
    }

    QPdfDocumentRenderOptions renderOptions;
    renderOptions.setRenderFlags(QPdfDocumentRenderOptions::RenderFlag::TextAliased);
    renderOptions.setScaledSize(pageSizePixels);

    QString cont;
    std::cout << "Printer: " << printer.printerName().toStdString() << "\n";
    std::cout << "Paper size(mm): " << mmWidth << "x" << mmHeight << "\n";
    std::cout << "Start printing? (Yes/No):";
    QTextStream qin(stdin);
    cont = qin.readLine().trimmed().toLower();

    if (cont == "yes" || cont == "y" || cont == "ye" || cont.isEmpty()) {
        std::cout << "Printing started..." << std::endl;
    } else {
        std::cout << "Printing canceled." << std::endl;
        return -1;
    }

    QPainter painter;
    painter.begin(&printer);

    for(int i = 0; i < pdfDoc.pageCount(); i++) {
        if(i > 0) printer.newPage();

        QImage pageImage = pdfDoc.render(i, pageSizePixels, renderOptions);

        painter.drawImage(printer.pageRect(QPrinter::DevicePixel), pageImage);
    }

    painter.end();


    return 0;
}