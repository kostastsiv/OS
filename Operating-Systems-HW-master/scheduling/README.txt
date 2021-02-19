Giorgos Koffas (AEM 2389): gkoffas@uth.gr
Michalis Charatzoglou (AEM: 2352): mcharatzoglou@uth.gr
Konstantinos Tsivgiouras (AEM: 2378) ktsivgiouras@uth.gr

PROCESSES:
    Process1
    Process2
    Process3
    Process4

GOODNESS:
    INTERACTIVE:
        SMALL:
          Average RunTime: 150ms
          Average WaitTime:  610ms
          Average CompletionTime: 760ms
          Total time: 929ms
        LARGE:
          Average RunTime: 700ms
          Average WaitTime:  3754ms
          Average CompletionTime: 4454ms
          Total time: 5669ms


    NONINTERACTIVE:
      SMALL:
          Average RuntTime: 150ms
          Average WaitTime: 551.5ms
          Average CompletionTime: 701.5ms
          Total time: 749ms
        LARGE:
          Average RuntTime: 700ms
          Average WaitTime: 2506.75ms
          Average CompletionTime: 3206.75ms
          Total time: 3549ms

    MIXED:	/* Both interactive and non-interactive */
        SMALL:
          Average RunTime: 150ms
          Average WaitTime: 551.5ms
          Average CompletionTime: 701.5ms
          Total time: 749ms
        LARGE:
          Average RunTime: 700ms
          Average WaitTime: 3004ms
          Average CompletionTime: 3704ms
          Total time: 5519ms

PURE_SJF:
    INTERACTIVE:
        SMALL:
          Average RunTime: 150ms
          Average WaitTime: 603.5ms
          Average CompletionTime: 753.5ms
          Total Time: 889ms
        LARGE:
          Average RunTime: 700ms
          Average WaitTime: 3131.5ms
          Average CompletionTime: 3831.5ms
          Total time: 4189ms

      NONINTERACTIVE:
        SMALL:
          Average RunTime: 150ms
          Average WaitTime: 584.75ms
          Average CompletionTime: 734.75ms
          Total time: 760ms
        LARGE:
          Average RunTime: 700ms
          Average WaitTime: 2784.75ms
          Average CompletionTime: 3484.75ms
          Total time: 3510ms

    MIXED:
        SMALL:
          Average RunTime: 150ms
          Average WaitTime: 609.75ms
          Average CompletionTime: 759.75ms
          Total time: 760ms
        LARGE:
          Average RunTime: 700ms
          Average WaitTime: 3021.5ms
          Average CompletionTime: 3721.5ms
          Total time: 4909ms


NOTES*

  When running the interactive and non-interactive profiles for both goodness and pure SJF, we can observe that running with Goodness has a lesser average wait time, meaning more responsiveness by the system, which is reasonable considering the accuracy that comes together with the extra factor of time spent waiting in the ready queue.
  We can also observe that the pure SJF scheduling runs better on non-interactive processes, which also makes sense, since an interactive process can spend a lot of its time on I/O, not running on the CPU.
  Generally speaking, the Goodness scheduling has better performance in all test cases.
