using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Reflection;
using Tasks;

namespace Tasks.Tests
{
    [TestClass]
    public class TradeDayProcessorTest
    {
        [TestMethod]
        public void Constructor_Assigns_ProvidedValues_ToPrivateFields()
        {
            Predicate<TradeDay> predicate = d => true;
            var processor = new TradeDayProcessor(3, "mydata.csv", predicate);

            var t = typeof(TradeDayProcessor);
            var numConsumersField = t.GetField("numConsumers", BindingFlags.NonPublic | BindingFlags.Instance);
            var tradeFileField = t.GetField("tradeFile", BindingFlags.NonPublic | BindingFlags.Instance);
            var testField = t.GetField("test", BindingFlags.NonPublic | BindingFlags.Instance);

            Assert.IsNotNull(numConsumersField);
            Assert.IsNotNull(tradeFileField);
            Assert.IsNotNull(testField);

            object? numVal = numConsumersField!.GetValue(processor);
            Assert.IsNotNull(numVal);
            Assert.IsTrue(numVal is int && (int)numVal == 3, "numConsumers expected 3");

            object? fileVal = tradeFileField!.GetValue(processor);
            Assert.IsNotNull(fileVal);
            Assert.AreEqual("mydata.csv", fileVal as string);

            object? testVal = testField!.GetValue(processor);
            Assert.AreSame(predicate, testVal);
        }

        [TestMethod]
        public void Constructor_Allows_Null_Predicate()
        {
            var processor = new TradeDayProcessor(1, "file.csv", null);
            var t = typeof(TradeDayProcessor);
            var testField = t.GetField("test", BindingFlags.NonPublic | BindingFlags.Instance);
            Assert.IsNotNull(testField);
            var val = testField!.GetValue(processor);
            Assert.IsNull(val);
        }
    }
}
