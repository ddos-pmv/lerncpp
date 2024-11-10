#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QUrl>
#include <QDebug>
#include <QApplication>

void downloadPdf(const QUrl &url, const QString &savePath) {
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);

    QObject::connect(reply, &QNetworkReply::finished, [reply, savePath]() {
        if (reply->error() == QNetworkReply::NoError) {
            QFile file(savePath);
            if (file.open(QIODevice::WriteOnly)) {
                file.write(reply->readAll());
                file.close();
                qDebug() << "PDF успешно скачан!";
            } else {
                qDebug() << "Ошибка открытия файла для записи.";
            }
        } else {
            qDebug() << "Ошибка при скачивании:" << reply->errorString();
        }
        reply->deleteLater();
    });
}


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QUrl pdfUrl("https://assets.codeforces.com/statements/589.pdf");
    QString savePath = "C:/Users/perli/Downloads/file.pdf";
    downloadPdf(pdfUrl, savePath);

    return app.exec();
}

