/*
 * scheduler.c
 *
 * Created on: 18 thg 11, 2025
 * Author: PC LEGION
 */

#include "scheduler.h"
#include <stdio.h>

sTasks SCH_tasks_G[SCH_MAX_TASKS];
uint8_t current_index_task = 0;

static void SCH_Delete_Task_at_Index(uint8_t index) {
    if (index >= current_index_task) return;

    if (index < current_index_task - 1) {
        SCH_tasks_G[index + 1].Delay += SCH_tasks_G[index].Delay;
    }

    for (int i = index; i < current_index_task - 1; i++) {
        SCH_tasks_G[i] = SCH_tasks_G[i + 1];
    }

    SCH_tasks_G[current_index_task - 1].pTask = NULL;
    SCH_tasks_G[current_index_task - 1].Delay = 0;
    SCH_tasks_G[current_index_task - 1].Period = 0;
    SCH_tasks_G[current_index_task - 1].RunMe = 0;
    current_index_task--;
}

void SCH_Init(void){
	current_index_task = 0;
    for (int i = 0; i < SCH_MAX_TASKS; i++) {
        SCH_tasks_G[i].pTask = NULL;
        SCH_tasks_G[i].Delay = 0;
        SCH_tasks_G[i].Period = 0;
        SCH_tasks_G[i].RunMe = 0;
        SCH_tasks_G[i].TaskID = 0;
    }
}

void SCH_Add_Task ( void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD ){
    if (current_index_task >= SCH_MAX_TASKS) {
        return;
    }

    uint32_t Time_to_Run = DELAY;
    int i = 0;

    while ((i < current_index_task) && (Time_to_Run >= SCH_tasks_G[i].Delay)) {
        Time_to_Run -= SCH_tasks_G[i].Delay;
        i++;
    }

    for (int j = current_index_task; j > i; j--) {
        SCH_tasks_G[j] = SCH_tasks_G[j - 1];
    }

    SCH_tasks_G[i].pTask = pFunction;
    SCH_tasks_G[i].Delay = Time_to_Run;
    SCH_tasks_G[i].Period = PERIOD;
    SCH_tasks_G[i].RunMe = 0;
    SCH_tasks_G[i].TaskID = current_index_task;

    if (i < current_index_task) {
        SCH_tasks_G[i + 1].Delay -= Time_to_Run;
    }

    current_index_task++;
}

void SCH_Update(void)
{
    if (current_index_task > 0 && SCH_tasks_G[0].Delay > 0){
        SCH_tasks_G[0].Delay--;
    }
}

void SCH_Dispatch_Tasks(void){
    while (current_index_task > 0 && SCH_tasks_G[0].Delay == 0) {
        SCH_tasks_G[0].RunMe += 1;

        if (SCH_tasks_G[0].RunMe > 0){
            SCH_tasks_G[0].RunMe--;
            (*SCH_tasks_G[0].pTask)();
        }

        if (SCH_tasks_G[0].Period > 0) {
            void (*temp_pTask)() = SCH_tasks_G[0].pTask;
            uint32_t temp_Period = SCH_tasks_G[0].Period;
            uint32_t temp_TaskID = SCH_tasks_G[0].TaskID;

            SCH_Delete_Task_at_Index(0);

            SCH_Add_Task(temp_pTask, temp_Period, temp_Period);
        } else {
            SCH_Delete_Task_at_Index(0);
        }
    }
}

void SCH_Delete_Task(uint32_t ID) {
    for (int i = 0; i < current_index_task; i++) {
        if (SCH_tasks_G[i].TaskID == ID) {
            SCH_Delete_Task_at_Index(i);
            return;
        }
    }
}

//
//
//#include "scheduler.h"
//#include <stdio.h>
//#include <string.h> // Cho memset
//
//sTasks SCH_tasks_G[SCH_MAX_TASKS];
//uint8_t current_heap_size = 0;
//uint32_t Current_System_Tick = 0; // Tick toàn cục, giả định tăng 1 mỗi lần ngắt định thời
//
//// --- CÁC HÀM TIỆN ÍCH RIÊNG (PRIVATE) CHO MIN-HEAP ---
//
//// Hoán đổi hai phần tử trong Heap
//static void swap_tasks(uint8_t i, uint8_t j) {
//    sTasks temp = SCH_tasks_G[i];
//    SCH_tasks_G[i] = SCH_tasks_G[j];
//    SCH_tasks_G[j] = temp;
//}
//
///**
// * @brief Duy trì thuộc tính Min-Heap bằng cách sàng phần tử xuống (Heapify Down)
// * @details Độ phức tạp O(log N). Tác vụ có AbsoluteTick nhỏ nhất sẽ ở trên cùng.
// */
//static void heapify_down(uint8_t i) {
//    uint8_t smallest = i;
//    uint8_t left = 2 * i + 1;
//    uint8_t right = 2 * i + 2;
//
//    // So sánh với nút con bên trái
//    if (left < current_heap_size && SCH_tasks_G[left].AbsoluteTick < SCH_tasks_G[smallest].AbsoluteTick) {
//        smallest = left;
//    }
//
//    // So sánh với nút con bên phải
//    if (right < current_heap_size && SCH_tasks_G[right].AbsoluteTick < SCH_tasks_G[smallest].AbsoluteTick) {
//        smallest = right;
//    }
//
//    // Nếu nút nhỏ nhất không phải là nút hiện tại
//    if (smallest != i) {
//        swap_tasks(i, smallest);
//        heapify_down(smallest); // Tiếp tục sàng xuống
//    }
//}
//
///**
// * @brief Duy trì thuộc tính Min-Heap bằng cách sàng phần tử lên (Heapify Up)
// * @details Độ phức tạp O(log N).
// */
//static void heapify_up(uint8_t i) {
//    uint8_t parent = (i - 1) / 2;
//
//    // Nếu AbsoluteTick của nút con nhỏ hơn nút cha
//    if (i > 0 && SCH_tasks_G[i].AbsoluteTick < SCH_tasks_G[parent].AbsoluteTick) {
//        swap_tasks(i, parent);
//        heapify_up(parent); // Tiếp tục sàng lên
//    }
//}
//
///**
// * @brief Xóa và trả về tác vụ ở gốc (tác vụ sẽ chạy sớm nhất)
// * @details Độ phức tạp O(log N).
// */
//static sTasks SCH_Extract_Min() {
//    // Lưu tác vụ gốc
//    sTasks min_task = SCH_tasks_G[0];
//
//    // Thay thế gốc bằng tác vụ cuối cùng
//    SCH_tasks_G[0] = SCH_tasks_G[current_heap_size - 1];
//    current_heap_size--;
//
//    // Duy trì thuộc tính Heap
//    heapify_down(0);
//
//    return min_task;
//}
//
//// --- CÁC HÀM CHÍNH (PUBLIC) ---
//
//void SCH_Init(void){
//	current_heap_size = 0;
//    Current_System_Tick = 0;
//    // Khởi tạo tất cả các phần tử
//    for (int i = 0; i < SCH_MAX_TASKS; i++) {
//        SCH_tasks_G[i].pTask = NULL;
//        SCH_tasks_G[i].AbsoluteTick = 0;
//        SCH_tasks_G[i].Period = 0;
//        SCH_tasks_G[i].RunMe = 0;
//    }
//}
//
///**
// * @brief Thêm tác vụ vào Heap (tối ưu hóa O(log N))
// */
//void SCH_Add_Task ( void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD ){
//    if (current_heap_size >= SCH_MAX_TASKS) {
//        // Lỗi: Heap đã đầy
//        return;
//    }
//
//    // 1. CHÈN TÁC VỤ VÀO VỊ TRÍ CUỐI
//    uint8_t new_index = current_heap_size;
//
//    SCH_tasks_G[new_index].pTask = pFunction;
//    // Tính Total Absolute Delay
//    SCH_tasks_G[new_index].AbsoluteTick = Current_System_Tick + DELAY;
//    SCH_tasks_G[new_index].Period = PERIOD;
//    SCH_tasks_G[new_index].RunMe = 0;
//
//    current_heap_size++;
//
//    // 2. SÀNG LÊN (HEAPIFY UP) để đưa tác vụ vào đúng vị trí (O(log N))
//    heapify_up(new_index);
//}
//
//
///**
// * @brief Cập nhật bộ lập lịch (gọi trong ngắt định thời)
// * @details Độ phức tạp O(1) - Chỉ cập nhật biến tick.
// */
//void SCH_Update(void)
//{
//    Current_System_Tick++;
//    // KHÔNG cần cập nhật AbsoluteTick của các tác vụ trong Heap!
//    // Độ trễ của chúng được so sánh với Current_System_Tick trong Dispatch.
//}
//
//
///**
// * @brief Kiểm tra và thực thi các tác vụ đã sẵn sàng
// * @details Độ phức tạp O(1) trong trường hợp thông thường.
// * O(log N) khi có tác vụ hết hạn (Xóa gốc + Thêm lại).
// */
//void SCH_Dispatch_Tasks(void){
//    // Kiểm tra liên tục miễn là tác vụ đầu tiên đã hết thời gian chờ
//    // Tác vụ sớm nhất luôn là gốc Heap (chỉ số 0)
//    while (current_heap_size > 0 && SCH_tasks_G[0].AbsoluteTick <= Current_System_Tick) {
//
//        // 1. TRÍCH XUẤT TÁC VỤ GỐC (O(log N))
//        // Hàm Extract_Min sẽ xóa gốc và tự động sắp xếp lại Heap
//        sTasks task_to_run = SCH_Extract_Min();
//
//        task_to_run.RunMe += 1;
//
//        if (task_to_run.RunMe > 0){
//            task_to_run.RunMe--;
//
//            // Thực thi tác vụ
//            (*task_to_run.pTask)();
//        }
//
//        // 2. TÁI LẬP LỊCH HOẶC KẾT THÚC
//        if (task_to_run.Period > 0) {
//            // Tác vụ định kỳ -> Tái lập lịch (O(log N))
//
//            // AbsoluteTick mới = Thời điểm hiện tại + Period.
//            // KHÔNG dùng Current_System_Tick + Period để tránh trôi thời gian (jitter)
//            // Thay vào đó, dùng AbsoluteTick cũ + Period.
//            uint32_t next_absolute_tick = task_to_run.AbsoluteTick + task_to_run.Period;
//
//            // Nếu thời điểm chạy kế tiếp vẫn nhỏ hơn hoặc bằng thời điểm hiện tại,
//            // nghĩa là hệ thống bị quá tải, ta cố gắng bắt kịp:
//            if (next_absolute_tick <= Current_System_Tick) {
//                 next_absolute_tick = Current_System_Tick + task_to_run.Period;
//            }
//
//            // Thêm lại vào Heap
//            SCH_Add_Task(task_to_run.pTask, next_absolute_tick - Current_System_Tick, task_to_run.Period);
//        } else {
//            // Tác vụ chạy một lần (One-shot) -> Đã bị xóa bởi Extract_Min
//        }
//    }
//}
//
//// Hàm này không còn hiệu quả O(N) vì cần tìm kiếm toàn bộ Heap
//// Chúng ta sẽ bỏ qua việc triển khai chi tiết cho phiên bản Heap,
//// vì nó yêu cầu tìm kiếm tuyến tính O(N) trước khi xóa O(log N).
//void SCH_Delete_Task(uint32_t ID) {
//    // Để xóa một tác vụ bất kỳ, cần:
//    // 1. Tìm kiếm O(N)
//    // 2. Tạm thời đổi khóa sắp xếp (AbsoluteTick) thành -vô cùng (nhỏ nhất)
//    // 3. Gọi Extract_Min O(log N)
//    // Hoặc đơn giản hơn:
//    // 1. Tìm kiếm O(N)
//    // 2. Thay thế bằng phần tử cuối
//    // 3. Giảm size
//    // 4. Gọi heapify_down HOẶC heapify_up tùy thuộc vào giá trị mới.
//    // -> Rất phức tạp cho một hàm ít dùng.
//}

