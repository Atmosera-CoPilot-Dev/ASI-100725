using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading;
using System.Threading.Tasks;   
using System.Collections.Concurrent;
using System.Diagnostics;

namespace Tasks
{
    class Program
    {
        static void Main()
        {
            const int NUM_CONSUMERS = 10;

            TradeDayProcessor processor = new TradeDayProcessor(NUM_CONSUMERS,
                                                                @"..\..\..\dowjones.csv",
                                                                day => (day.Close - day.Open) / day.Open > 0.05);

            CancellationTokenSource src = new CancellationTokenSource();
            Task cancelTask = new Task(Canceller, src);
            cancelTask.Start();

            Stopwatch sw = Stopwatch.StartNew();

            bool canceled = false;
            try
            {
                processor.Start(src.Token);
            }
            catch (OperationCanceledException)
            {
                canceled = true;
                Console.WriteLine("Processing canceled by user.");
            }
            catch (AggregateException ae)
            {
                ae = ae.Flatten();
                foreach (var ex in ae.InnerExceptions)
                {
                    if (ex is OperationCanceledException)
                    {
                        canceled = true;
                        continue;
                    }
                    Console.WriteLine("Unexpected error: {0}", ex);
                }
            }

            int totalMatches = processor.GetMatchingCount();

            Console.WriteLine("Total processing time {0}", sw.Elapsed);
            Console.WriteLine(canceled
                                ? $"Total matches (partial) {totalMatches}"
                                : $"Total matches {totalMatches}");
        }

        private static void Canceller(object o)
        {
            CancellationTokenSource src = (CancellationTokenSource)o;
            Console.WriteLine("press enter to cancel");
            Console.ReadLine();
            src.Cancel();
        }
    }
}
