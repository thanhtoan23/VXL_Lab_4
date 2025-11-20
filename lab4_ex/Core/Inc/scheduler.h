/*
 * scheduler.h
 *
 * Created on: 18 thg 11, 2025
 * Author: PC LEGION
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include<stdint.h>

typedef uint8_t unit8_t;

typedef struct {
	void (*pTask)(void);
	uint32_t Delay;
	uint32_t Period;
	unit8_t  RunMe;

	uint32_t TaskID;
} sTasks;

#define SCH_MAX_TASKS 40

void SCH_Init(void);

void SCH_Add_Task ( void (*pFunction)(),
		uint32_t DELAY,
		uint32_t PERIOD);

void SCH_Update(void);          // O(1)
void SCH_Dispatch_Tasks(void);  // O(1) hoặc O(N)
void SCH_Delete_Task(uint32_t ID);

#endif /* INC_SCHEDULER_H_ */




//#ifndef SCHEDULER_H_
//#define SCHEDULER_H_
//
//#include <stdint.h>
//
//// Kích thước tối đa của bộ lập lịch
//#define SCH_MAX_TASKS 10
//
//// Cấu trúc Node Task (sẽ được lưu trong Heap)
//typedef struct {
//    void (*pTask)();
//    uint32_t AbsoluteTick; // Khóa sắp xếp: Thời điểm tuyệt đối (Total Absolute Delay)
//    uint32_t Period;
//    uint8_t RunMe;
//} sTasks;
//
//// Mảng Heap: Lưu trữ các tác vụ, được sắp xếp theo AbsoluteTick
//extern sTasks SCH_tasks_G[SCH_MAX_TASKS];
//extern uint8_t current_heap_size; // Kích thước hiện tại của Heap
//
//// Biến tick toàn cục (đếm thời gian tuyệt đối)
//extern uint32_t Current_System_Tick;
//
//// --- CÁC HÀM CHÍNH (PUBLIC) ---
//void SCH_Init(void);
//void SCH_Update(void);
//void SCH_Dispatch_Tasks(void);
//// Hàm Add_Task mới: Thêm tác vụ vào Heap
//void SCH_Add_Task ( void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD );
//void SCH_Delete_Task(uint32_t ID); // Không dùng TaskID trong ví dụ Heap này, nhưng vẫn giữ.
//
//#endif /* SCHEDULER_H_ */
