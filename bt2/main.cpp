#include <stdio.h>

struct SmartDevice {
    float voltage;
    float current;
    int status;
};

struct DeviceOperation {
    float ratedPowerKW;
    int absentMinutes;
    float operatingHours;
};

int main() {
    struct SmartDevice device;
    struct DeviceOperation op;

    printf("=== NHAP THONG SO THIET BI ===\n");
    printf("Nhap dien ap (V): ");
    scanf("%f", &device.voltage);
    printf("Nhap dong dien (A): ");
    scanf("%f", &device.current);
    printf("Nhap trang thai (1 - Bat, 0 - Tat): ");
    scanf("%d", &device.status);

    printf("\n=== NHAP THONG SO CAM BIEN & VAN HANH ===\n");
    printf("Nhap thoi gian vang nguoi (phut): ");
    scanf("%d", &op.absentMinutes);
    printf("Nhap cong suat dinh muc (kW): ");
    scanf("%f", &op.ratedPowerKW);
    printf("Nhap so gio van hanh trong thang: ");
    scanf("%f", &op.operatingHours);

    if (device.voltage < 0 || device.current < 0 || op.absentMinutes < 0 || op.ratedPowerKW < 0) {
        printf("\n[LOI]: Du lieu cam bien/thong so am khong hop le! Huy thao tac.\n");
        return 1;
    }

    if (op.operatingHours <= 0 || op.operatingHours > 744) {
        printf("\n[LOI]: So gio van hanh phai lon hon 0 va khong vuot qua 744 gio (31 ngay)!\n");
        return 1;
    }

    printf("\n=== XU LY NGHIEMP VU ===\n");

    if (device.current > 30.0f) {
        device.status = 0;
        printf("[CANH BAO]: Dong dien vuot qua 30A! Kich hoat che do ngat khan cap de phong chay no.\n");
    }

    if (device.status == 1 && op.absentMinutes >= 15) {
        device.status = 0;
        printf("[TIET KIEM DIEN]: Phong trong va vang nguoi tu 15 phut tro len. Da tu dong tat thiet bi.\n");
    }

    float totalKWh = op.ratedPowerKW * op.operatingHours;
    double totalCost = 0;

    float tempKWh = totalKWh;

    if (tempKWh > 200) {
        totalCost += (tempKWh - 200) * 2729;
        tempKWh = 200;
    }
    if (tempKWh > 100) {
        totalCost += (tempKWh - 100) * 2167;
        tempKWh = 100;
    }
    if (tempKWh > 50) {
        totalCost += (tempKWh - 50) * 1866;
        tempKWh = 50;
    }
    if (tempKWh > 0) {
        totalCost += tempKWh * 1806;
    }

    printf("\n=== BAO CAO CUOI CUNG ===\n");
    printf("Trang thai thiet bi: %s\n", device.status == 1 ? "BAT" : "TAT");
    printf("Tong dien nang tieu thu: %.2f kWh\n", totalKWh);
    printf("Tong tien dien phai tra (chua VAT): %.0f VND\n", totalCost);

    return 0;
}
