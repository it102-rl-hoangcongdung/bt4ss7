#include <stdio.h>

struct SmartDevice {
    char device_id[20];
    char device_name[50];
    int status;
    float power_watt;
};

struct EnergySensor {
    float operating_voltage;
    float current_ampere;
    int motion_idle_time;
};

struct PowerReport {
    float total_power_watt;
    float total_current_ampere;
    float estimated_kwh;
    int safety_warning;
};

int main() {
    struct SmartDevice ac = {"DEV_AC_01", "Dieu hoa nhiet do Phong khach", 1, 1500.0};
    struct SmartDevice light = {"DEV_LT_01", "He thong den chieu sang", 1, 300.0};
    struct EnergySensor sensor = {220.0, 14.5, 20};
    struct PowerReport report = {0.0, 0.0, 0.0, 0};

    printf("[INFO] He thong Smart Home Central Gateway dang khoi dong...\n");
    printf("[INFO] Kiem tra cam bien hien dien: Thoi gian khong co nguoi = %d phut.\n", sensor.motion_idle_time);

    if (sensor.motion_idle_time > 15) {
        printf("[ACTION] Phat hien phong trong qua 15 phut! Tu dong tat Dieu hoa.\n");
        ac.status = 0;
        ac.power_watt = 0.0;
    }

    if (ac.status == 1) {
        report.total_power_watt += ac.power_watt;
    }
    if (light.status == 1) {
        report.total_power_watt += light.power_watt;
    }

    report.total_current_ampere = report.total_power_watt / sensor.operating_voltage;

    if (report.total_current_ampere > 30.0) {
        report.safety_warning = 1;
    } else {
        report.safety_warning = 0;
    }

    report.estimated_kwh = (report.total_power_watt * 2.5) / 1000.0;

    printf("\n=======================================================\n");
    printf("       SMART HOME IOT GATEWAY - DASHBOARD BAN DEM     \n");
    printf("=======================================================\n");
    printf("%-18s | %-15s | %-10s | %-10s\n", "Ma Thiet Bi", "Ten Thiet Bi", "Trang Thai", "Cong Suat");
    printf("-------------------------------------------------------\n");
    printf("%-18s | %-15s | %-10s | %.1fW\n", ac.device_id, ac.device_name, ac.status == 1 ? "ON" : "OFF", ac.power_watt);
    printf("%-18s | %-15s | %-10s | %.1fW\n", light.device_id, light.device_name, light.status == 1 ? "ON" : "OFF", light.power_watt);
    printf("=======================================================\n");
    printf("[BAO CAO NANG LUONG TONG HOP]\n");
    printf(" - Tong cong suất tai: %.2f W\n", report.total_power_watt);
    printf(" - Tong dong dien tieu thu: %.2f A\n", report.total_current_ampere);
    printf(" - Dien nang uoc tinh (2.5h): %.3f kWh\n", report.estimated_kwh);
    printf(" - Trang thai an toan he thong: %s\n", report.safety_warning == 1 ? "CANH BAO QUA TAI NGUY HIEM (>30A)!" : "AN TOAN (Binh thuong)");
    printf("=======================================================\n");

    return 0;
}
