#include <iostream>
#include <QApplication>
#include <QPrinter>
#include <QPainter>
#include <QPdfDocument>
#include <QMessageBox>
#include <QPageSize>
#include <QPdfDocumentRenderOptions>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Path to the PDF file
    QString pdfFilePath = "/Users/sergejperlin/CLionProjects/sportProgramming/xprinter/hello.pdf";  // Replace with your path

    QPdfDocument pdfDoc;
    if (pdfDoc.load(pdfFilePath) != QPdfDocument::Error::None) {
        QMessageBox::warning(nullptr, "Error", "Failed to load PDF.");
        return -1;
    }

    QPrinter printer(QPrinter::HighResolution);
    printer.setPrinterName("Xprinter xp-365b");
    printer.setFullPage(true);

    // Set the page size for the label (4 cm x 3 cm)
    QPageSize pageSize(QSizeF(40.0, 30.0), QPageSize::Millimeter);
    printer.setPageSize(pageSize);

    if (!printer.isValid()) {
        QMessageBox::warning(nullptr, "Error", "Printer not found.");
        return -1;
    }

    QPainter painter;
    if (!painter.begin(&printer)) {
        QMessageBox::warning(nullptr, "Error", "Failed to start drawing on the printer.");
        return -1;
    }

    // Get the page size of the printer in millimeters
    QRectF rectF = printer.pageRect(QPrinter::Millimeter);
    QRect imageRect = rectF.toRect();
    QSize imageSize(imageRect.size());

    // Render the first page of the PDF
    QImage renderedPage = pdfDoc.render(0, imageSize, QPdfDocumentRenderOptions());


    std::cout << printer.resolution();
    // Scale the image to fit the label size exactly
    QImage scaledImage = renderedPage.scaled(imageRect.size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    painter.drawImage(imageRect, scaledImage);  // Draw the image on the printer

    painter.end();  // End the printing

    QMessageBox::information(nullptr, "Success", "PDF successfully sent to the printer.");
    return 0;
}
