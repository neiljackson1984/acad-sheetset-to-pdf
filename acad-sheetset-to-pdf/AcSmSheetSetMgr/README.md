# AcSmSheetSetMgr
 
        public void CreateAcSmDatabase1()
        {
            AcSmDatabase wDB = new AcSmDatabase();
            XmlDocument res = wDB.toXML();
            res.Save("test1.xml");
            wDB.SaveAsDstFile("test1.dst");
        }

        public void CreateAcSmDatabase2()
        {
            AcSmDatabase wDB = new AcSmDatabase();
            wDB.SetName("test2");
            wDB.AddSubset("testSubset1");
            wDB.SaveXML("test2.xml");
            wDB.SaveAsDstFile("test2.dst");
        }

        public void CreateAcSmDatabase3()
        {
            AcSmDatabase wDB = new AcSmDatabase();
            wDB.SetName("test3");
            wDB.SetCustomProperty("testProperty", "testValue");
            //
            wDB.SaveXML("test3.xml");
            wDB.SaveAsDstFile("test3.dst");
        }
