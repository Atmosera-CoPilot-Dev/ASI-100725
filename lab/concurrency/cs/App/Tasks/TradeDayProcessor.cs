using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections.Concurrent;
using System.IO;
using System.Threading;
using System.Threading.Tasks;
using System.Globalization;

namespace Tasks
{
    class TradeDayProcessor
    {
        int numConsumers;
        string tradeFile;
        Predicate<TradeDay> test;

        public TradeDayProcessor(int numConsumers, string tradeFile, Predicate<TradeDay> test)
        {
            this.numConsumers = numConsumers;
            this.tradeFile = tradeFile;
            this.test = test;
        }

        public void Start()
        {
        }

        public int GetMatchingCount()
        {
            try
            {
            }
            catch (AggregateException x)
            {
            }

            return -1;
        }
        
        private void GenerateTradeDays()
        {
        }

        private int ConsumeTradeDays()
        {
            int matchingDays = 0;
            return matchingDays;
        }

        private IEnumerable<TradeDay> ReadStockData()
        {
            using (StreamReader sr = new StreamReader(tradeFile))
            {
                string line = null;
                sr.ReadLine();
                while ((line = sr.ReadLine()) != null)
                {
                    TradeDay day = ParseTradeEntry(line);
                    yield return day;
                }
            }
        }

        private static TradeDay ParseTradeEntry(string entry)
        {
            string[] items = entry.Split(',');

            TradeDay ret = new TradeDay();
            ret.Date = DateTime.Parse(items[0]);
            ret.Open = double.Parse(items[1], NumberFormatInfo.InvariantInfo);
            ret.High = double.Parse(items[2], NumberFormatInfo.InvariantInfo);
            ret.Low = double.Parse(items[3], NumberFormatInfo.InvariantInfo);
            ret.Close = double.Parse(items[4], NumberFormatInfo.InvariantInfo);
            ret.Volume = long.Parse(items[5], NumberFormatInfo.InvariantInfo);
            ret.AdjClose = double.Parse(items[6], NumberFormatInfo.InvariantInfo);

            return ret;
        }
    }
}
