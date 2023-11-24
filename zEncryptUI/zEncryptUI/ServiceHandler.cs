using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace zEntryptUI
{
    internal class ServiceHandler
    {
        private static ServiceHandler? _instance = null;
        private ServiceHandler()
        {
        }
        public static ServiceHandler GetInstance()
        {
            if (_instance == null)
            {
                _instance = new ServiceHandler();
            }
            return _instance;
        }

        public const string servicePath = "resources\\zEncrypter.exe";
        public string configPath = "config.in";

        public void StartEngine()
        {
            Process process = new Process();
            // Configure the process using the StartInfo properties.
            process.StartInfo.FileName = servicePath;
            process.StartInfo.ArgumentList.Add("-c");
            process.StartInfo.ArgumentList.Add(configPath);
            process.StartInfo.WindowStyle = ProcessWindowStyle.Normal;
            process.Start();
            process.WaitForExit();
        }
    }
}
